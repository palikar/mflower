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



}
