#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <initializer_list>
#include <ranges.hpp>
#include <stdexcept>
#include <memory>

#include "shape.hpp"



namespace mf
{

namespace ut = ranges;


// Forward declarations
struct EvaluationContext;
struct ReturnHandler;

template<typename T>
class DataBlock
{
  public:

    explicit DataBlock(Shape a_shape) : m_shape(std::move(a_shape))
    {
        this->init_memory();
    }
    
    explicit DataBlock(size_t i) : m_shape(i)
    {
        this->init_memory();
    }

    DataBlock(size_t i, size_t j) : m_shape({i, j})
    {
        this->init_memory();
    }

    DataBlock(size_t i, size_t j, size_t k) : m_shape({i, j, k})
    {
        this->init_memory();
    }

    ~DataBlock()
    {
    };

    size_t dims() const
    {
        return m_shape.get_dims().size();
    }

    size_t length() const
    {
        return m_shape.size();
    }

    T* data() const
    {
        return m_buffer;
    }

    T at(size_t a_index) const
    {
        return m_buffer[a_index];
    }

    T operator()(size_t i)
    {
        if (this->dims() != 1)
            throw std::runtime_error("The data block must have dimension of 1");
                
        return m_buffer[m_shape.get_offset(i)];
    }

    T operator()(size_t i, size_t j)
    {
        if (this->dims() != 2)
            throw std::runtime_error("The data block must have dimension of 2");
        
        return m_buffer[m_shape.get_offset(i, j)];
    }

    T operator()(size_t i, size_t j, size_t k)
    {
        if (this->dims() != 3)
            throw std::runtime_error("The data block must have dimension of 3");
        
        return m_buffer[m_shape.get_offset(i,j,k)];
    }

    T operator()(std::initializer_list<size_t> indices)
    {
        if (this->dims() != std::size(indices))
            throw std::runtime_error("The data block must have dimension of 1");
        return m_buffer[m_shape.get_offset(indices)];
    }

    void set_val(T val, size_t i)
    {
        m_buffer[m_shape.get_offset(i)]  = val;
    }

    void set_val(T val, size_t i, size_t j)
    {
        m_buffer[m_shape.get_offset(i, j)]  = val;
    }

    void set_val(T val, size_t i, size_t j, size_t k)
    {
        m_buffer[m_shape.get_offset(i, j, k)]  = val;
    }

    void set_val(T val, std::initializer_list<size_t> indices)
    {
        m_buffer[m_shape.get_offset(indices)]  = val;
    }

  protected:
    
    void init_memory()
    {
        const size_t size = m_shape.size();
        m_element_size = sizeof(T);
        m_buffer = (T*) malloc(m_element_size * size);

    }

    T *m_buffer;
    size_t m_element_size;
    Shape m_shape;
};



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
    std::shared_ptr<DataBlock<double>> m_data;
};

class Constant : public Tensor
{
  public:
    Constant(double value) : Tensor("constant:0")
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
    Variable(std::string name) : Tensor(name)
    {}
    virtual ~Variable()
    {};

    void eval(EvaluationContext a_context, ReturnHandler a_handler) override;
  private:
};



}
