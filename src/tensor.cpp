#include <iostream>

#include "tensor.hpp"


Tensor::Tensor(const TensorType type, const Shape shape):
  type(type),
  shape(shape)
{

}


Tensor::Tensor(const TensorType type):
  type(type)
{
}


Tensor::~Tensor()
{

}


double TensorArray::evaluate(const Scope& scope)
{
  return 0;
}


TensorArray:: TensorArray(ArrayType type):
  Tensor(TensorType::Array, Shape(-1)),
  arr_type(type)
{
  
}

void TensorArray::add_tensor(Tensor* t)
{
  this->tensors.push_back(t);
}

std::vector<Tensor*>& TensorArray::get_elements()
{
  return this->tensors;
}

TensorArray::~TensorArray()
{}

Constant::Constant(double value):
  Tensor(TensorType::Scalar, Shape(0)),
  value(value)
{
  
}
  
double Constant::evaluate(const Scope& scope)
{
  return this->value;

}


Constant::~Constant()
{

}

Variable::Variable(const std::string name) :
  Tensor(TensorType::Scalar,Shape(0)),
  name(name)
{
  
  
}
  
double Variable::evaluate(const Scope& scope)
{
  return scope.get_variable_value(this->name);
}




Variable::~Variable ()
{

}
