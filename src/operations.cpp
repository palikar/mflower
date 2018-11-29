#include <cmath>
#include <iostream>

#include "operations.hpp"



double Add::evaluate(const Scope& scope)
{
	return lhs->evaluate(scope) + rhs->evaluate(scope);
}


double Sub::evaluate(const Scope& scope)
{
	return  rhs->evaluate(scope) - lhs->evaluate(scope);
}


double Multiply::evaluate(const Scope& scope)
{
	return lhs->evaluate(scope) * rhs->evaluate(scope);
}


double Devide::evaluate(const Scope& scope)
{
	return rhs->evaluate(scope) / lhs->evaluate(scope);
}



double Exp::evaluate(const Scope& scope)
{
  return std::exp(this->exponent->evaluate(scope));
}


double Pow::evaluate(const Scope& scope)
{
  return std::pow(this->base->evaluate(scope),
                  this->exponent->evaluate(scope));
}


double Sum::evaluate(const Scope& scope)
{
  if (arr->type != TensorType::Array){
    std::cout << "Coont sum over non-array!" << "\n";
    exit(1);
  }
  double sum = 0;
  TensorArray* ta = (TensorArray*)arr;
  for (const auto& t : ta->get_elements())
  {
    sum += t->evaluate(scope);
  }
  return sum;
}
