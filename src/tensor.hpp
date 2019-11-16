#pragma once

#include "./utils/std_headers.hpp"
#include "./data.hpp"


namespace mf
{

struct EvaluationContext;
struct ReturnHandler;

namespace ut = ranges;
enum class TensorType
{
    Plain,
    Variable,
    Constant,
    Operation
};


class Tensor_Base
{
  public:
    Tensor_Base(std::string name) : m_id(std::move(name)), m_type(TensorType::Plain){}
    virtual ~Tensor_Base(){}

    virtual void eval(EvaluationContext, ReturnHandler) = 0;
    
    const std::string& name() const {return m_id;};
    DataBuffer_Base* block() { return data();}

  protected:
    virtual DataBuffer_Base* data() = 0;
    std::string m_id;
    TensorType m_type;
};


template<typename BlockType>
class Tensor : public Tensor_Base
{
  public:
    Tensor(std::string name) : Tensor_Base(std::move(name)), m_block(Shape(static_cast<size_t>(1)), 1){}
    Tensor(std::string name, BlockType blk) : Tensor_Base(std::move(name)), m_block(blk){}

    template<typename Block>
    void set_value(const Block&)
    {
        
    }

  protected:
    DataBuffer_Base* data() override { return &m_block; }
    BlockType m_block;
};

Tensor(std::string) -> Tensor<DynamicDataBuffer<double>>;

class Variable : public Tensor<DynamicDataBuffer<double>>
{
  public:
    Variable(std::string name) : Tensor(name)
    {
        m_block.init();
    }
    Variable(std::string name, Shape s) : Tensor(name, DynamicDataBuffer<double>(s, s.size()))
    {
        m_block.init();
    }
    virtual ~Variable() {};
    
    void eval(EvaluationContext, ReturnHandler) override;
};


typedef std::shared_ptr<Tensor_Base> TensorPtr;
typedef std::shared_ptr<Variable> VariablePtr;

 
}


