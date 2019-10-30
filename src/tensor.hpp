#pragma once

#include "./utils/std_headers.hpp"
#include "./data.hpp"

#include <ranges.hpp>



namespace mf
{

namespace ut = ranges;


// Forward declarations
struct EvaluationContext;
struct ReturnHandler;

enum class TensorType
{
    Plain,
    Variable,
    Constant,
    Operation    
};


class Tensor
{
    
  public:
    Tensor(std::string name) : m_id(std::move(name)), m_type(TensorType::Plain)
    {}

    virtual ~Tensor()
    {}
    
    template<size_t N>
    void init_data(double(&values)[N])
    {
        this->init_data(values, N);
    }

    template<size_t N, size_t M>
    void init_data(double(&values)[N][M])
    {
        this->init_data(&values[0][0], N, M);
    }

    void init_data(std::vector<double> values)
    {
        //TODO : create template method for generic container
        //TODO : create type train for conainer that is OK for
        // initializing a memory block
        this->init_data(values.data(), std::size(values));
    }
    
    void init_data(double* values, size_t size)
    {
        // TODO: this can be optimized; just copy the buffer in the location
        m_data = std::make_shared<DataBlock<double>>(size);
        for (size_t i = 0 ; i < size; ++i)
            m_data->set_val(values[i], i);
    }

    void init_data(double* values, size_t size_1, size_t size_2)
    {
        // TODO: this can either be column-major or row-major
        m_data = std::make_shared<DataBlock<double>>(size_1, size_2);
        for (size_t i = 0 ; i < size_1; ++i)
            for (size_t j = 0 ; j < size_1; ++j) 
                m_data->set_val(values[i+size_1*j], i, j);
    }

    void init_data(DataBlock<double> blk)
    {
        m_data = std::make_shared<DataBlock<double>>(blk);
    }


    template<typename ... T>
    double data(T... index) const
    {
        return m_data->operator()(index...);
    }

    DataBlock<double> block() { return *m_data;}
    
    virtual void eval(EvaluationContext i, ReturnHandler);

    const std::string& name() const {return m_id;};

  protected:
    std::string m_id;
    TensorType m_type;

    std::variant;
};

class Constant : public Tensor
{
  public:
    Constant(double value, std::string name) : Tensor(std::move(name))
    {
        this->init_data(&value, 1);
    }
    virtual ~Constant()
    {};

    void eval(EvaluationContext a_context, ReturnHandler a_handler) override;
  private:
};


class Variable : public Tensor
{
  public:
    Variable(std::string name) : Tensor(name) {}
    virtual ~Variable() {};
    void eval(EvaluationContext a_context, ReturnHandler a_handler) override;
};

class AddOp : public Tensor
{
  public:
    AddOp(std::string name) : Tensor(name) {}
    virtual ~AddOp() {};
    void eval(EvaluationContext a_context, ReturnHandler a_handler) override;
};



}
