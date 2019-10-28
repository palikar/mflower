#include <iostream>

#include "tensor.hpp"
#include "engine.hpp"


namespace mf
{


void Tensor::eval(EvaluationContext, ReturnHandler)
{
}


void Variable::eval(EvaluationContext a_context, ReturnHandler a_handler)
{
    a_handler.result(a_context.scope().get_variable_value(m_id));
}

void Constant::eval(EvaluationContext, ReturnHandler a_handler)
{
    a_handler.result(*m_data);
}


void AddOp::eval(EvaluationContext a_context, ReturnHandler a_handler)
{
    auto lhs = a_context.get_argument<0>();
    auto rhs = a_context.get_argument<1>();

    double res = lhs->data(0) + rhs->data(0);
    DataBlock<double> res_blk(1);

    res_blk.set_val(res, 0);
    a_handler.result(res_blk);
}



}
