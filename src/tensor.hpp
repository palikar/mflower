#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <initializer_list>
#include <ranges.hpp>

#include "shape.hpp"



namespace mf
{

namespace ut = ranges;


// Forward declarations
class EvaluationContext;
class ReturnHandler;

enum class TensorType
{
    Variable,
    Constant,
    Operation
};

class Tensor
{
  public:
    Tensor(std::string name, TensorType type) : m_id(std::move(name)), m_type(type)
    {}

    virtual ~Tensor()
    {}

    virtual void eval(EvaluationContext, ReturnHandler) = 0;

  private:
    std::string m_id;
    TensorType m_type;
};

template<typename T>
class DataBlock
{
  public:

    explicit DataBlock(size_t i) : m_shape({i})
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
        return m_buffer[m_shape.get_offset(i)];
    }

    T operator()(size_t i, size_t j)
    {
        return m_buffer[m_shape.get_offset(i, j)];
    }

    T operator()(size_t i, size_t j, size_t k)
    {
        return m_buffer[m_shape.get_offset(i,j,k)];
    }

    T operator()(std::initializer_list<size_t> indices)
    {
        return m_buffer[m_shape.get_offset(indices)];
    }

  private:

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

class Constant : public Tensor
{
  public:
    Constant(double value);
    virtual ~Constant();

    void eval(EvaluationContext a_context, ReturnHandler a_handler) override;
  private:
    DataBlock<float> m_databuffer;
};

}
