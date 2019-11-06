#pragma once

#include "./tensor.hpp"
#include "./engine.hpp"

namespace mf
{

template<typename BlockType>
class Constant : public Tensor<BlockType>
{
  public:
    Constant(BlockType blk, std::string name) : Tensor<BlockType>(std::move(name), blk)
    {
    }
    virtual ~Constant()
    {};

    void eval(EvaluationContext, ReturnHandler a_handler) override
    {
        a_handler.result(this->block());
    }
  private:
};

template<typename BlockType>
TensorPtr constant(BlockType value, std::string name)
{
    auto cons = std::make_shared<Constant<BlockType>>(value, name);
    engine()->add_tensor(cons);
    return cons;
}


}

