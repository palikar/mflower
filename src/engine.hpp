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


struct EvaluationContext
{

    // the engine
    // easy access to the scope

    // easy access to the arguments/dependencies
    // the dependencies should be evaluated
};

struct ReturnHandler
{


};


typedef std::shared_ptr<Tensor> TensorPtr;
typedef std::shared_ptr<Variable> VariablePtr;

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

    void eval(TensorPtr t_tens)
    {
        std::stack<std::pair<TensorPtr, std::vector<TensorPtr>>> ex_stack;
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
            ex_stack.push({cur_node, std::move(followers)});
        }

        EvaluationContext ev;
        
        while (!ex_stack.empty())
        {
            auto[node, deps] = ex_stack.top();

            

            ex_stack.pop();            
        }
        
    }
        
    

    
  private:
    Scope m_scope;
    Graph<std::shared_ptr<Tensor>> m_node_graph;
    std::vector<std::shared_ptr<Tensor>> m_tensor_buffer;
    std::unordered_map<std::string, DataBlock<double>> m_execution_buffer;
    
};

MFEngine* default_engine;

void init()
{
    default_engine = new MFEngine();
}
void finalize()
{
    delete default_engine;
}

MFEngine* engine()
{
    return default_engine; 
}


TensorPtr variable(std::string name, double value)
{
    auto var = std::make_shared<Variable>(name);
    var->init_data({value});
    default_engine->add_variable(var);
    return var;
}

TensorPtr constant(double value)
{
    auto cons = std::make_shared<Constant>(value);
    default_engine->add_tensor(cons);
    return cons;
}


void placeholder(std::string name){}

void add(TensorPtr lhs, TensorPtr rhs){}
void sub(TensorPtr lhs, TensorPtr rhs){}
void mult(TensorPtr lhs, TensorPtr rhs){}
void devide(TensorPtr lhs, TensorPtr rhs){}

void exp(TensorPtr base, TensorPtr exp){}


}
