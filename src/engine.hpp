#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <iterator>
#include <utility>
#include <memory>
#include <queue>
#include<stack>
#include <iostream>


#include "./tensor.hpp"
#include "./graph.hpp"
#include "./operations.hpp"
#include "./scope.hpp"

namespace mf
{

//Tracer - to track what is being executed
//Optimizer to keep the graph nice and clean
	

class MFEngine;
typedef std::shared_ptr<Tensor> TensorPtr;
typedef std::shared_ptr<Variable> VariablePtr;

struct EvaluationContext
{

    template<typename...TensType>
    EvaluationContext(MFEngine& t_engine, TensType... t_tensors);

    EvaluationContext(MFEngine& t_engine, std::vector<TensorPtr> t_tensors);
    

    template<size_t i>
    TensorPtr get_argument()
    {
        return m_args.at(i);
    }
    
    void update_variable(const std::string& name, TensorPtr value);
    void push_scope();
    Scope& scope();
    

  private:
    std::reference_wrapper<MFEngine> m_engine;
    std::vector<TensorPtr> m_args;
};

struct ReturnHandler
{
    ReturnHandler(MFEngine& t_engine, TensorPtr t_result_location) : m_engine(t_engine),
                                                                     m_result_location(t_result_location)
    {};
    // the tensors put their resutls here

    void result(DataBlock<double> blk)
    {
        m_result_location.get()->init_data(blk);
    }

    void operator=(const DataBlock<double> blk)
    {
        m_result_location.get()->init_data(blk);
    }

  private:
    std::reference_wrapper<MFEngine> m_engine;
    std::reference_wrapper<TensorPtr> m_result_location;
};

class MFEngine
{
  public:

    MFEngine()
    {}
    
    void add_tensor(TensorPtr t_tens, std::vector<TensorPtr> t_deps)
    {
        this->add_tensor(t_tens);
        for (auto t : t_deps) {
            m_node_graph.add_edge(t_tens->name(), t->name());
        }

    }

    void add_tensor(TensorPtr t_tens)
    {
        m_tensor_buffer.push_back(t_tens);
        m_node_graph.add_node(t_tens->name(), t_tens);
    }

    void add_variable(VariablePtr t_var)
    {
        add_tensor(t_var);
        m_scope.put_variable(t_var->name(), t_var->block());
    }

    TensorPtr eval(TensorPtr t_tens)
    {
        std::stack<std::pair<TensorPtr, std::vector<TensorPtr>>> exe_stack;
        std::queue<TensorPtr> nodes;
        nodes.push(t_tens);

        while(!nodes.empty())
        {
            auto cur_node = nodes.front();

            auto followers = m_node_graph.get_following_edges(cur_node->name());
            nodes.pop();
            for(auto& f : followers)
            {
                nodes.push(f);
            }
            exe_stack.push({cur_node, std::move(followers)});
        }

        while (!exe_stack.empty())
        {
            auto[node, deps] = exe_stack.top();
            exe_stack.pop();
            
            EvaluationContext ex(*this, deps);
            ReturnHandler rh(*this, node);
            node->eval(ex, rh);
        }

        
        return t_tens;
        
    }

    Scope& scope()
    {
        return m_scope;
    }
    
  private:
    Scope m_scope;
    Graph<std::shared_ptr<Tensor>> m_node_graph;
    std::vector<std::shared_ptr<Tensor>> m_tensor_buffer;
    std::unordered_map<std::string, DataBlock<double>> m_execution_buffer;
    
};

void init();
void finalize();
MFEngine* engine();
TensorPtr variable(std::string name, double value);
TensorPtr constant(double value, std::string name);

TensorPtr add(TensorPtr lhs, TensorPtr rhs, std::string name);

// void placeholder(std::string name){}
// void sub(TensorPtr lhs, TensorPtr rhs){}
// void mult(TensorPtr lhs, TensorPtr rhs){}
// void devide(TensorPtr lhs, TensorPtr rhs){}
// void exp(TensorPtr base, TensorPtr exp){}


}
