i#include <iostream>

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

size_t Tensor::get_size() const
{
  return this->data_size;
};


Tensor::~Tensor()
{

}


double* TensorArray::evaluate(const Scope& scope)
{
  return nullptr;
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
  Tensor(TensorType::Scalar, Shape())
{
  this->data_buffer = (double*) new double();
  *this->data_buffer = value;
  this->data_size = 1;
}

Constant::Constant(std::vector<double> values):
  Tensor(TensorType::Scalar, Shape(values.size()))
{
  this->data_buffer = (double*) new double[sizeof(double)*values.size()]();
  this->data_size = values.size();
  size_t index = 0;
  for(auto& val : values)
    this->data_buffer[index++] = val;
}


Constant::Constant(double* values, int columns, int rows):
  Tensor(TensorType::Scalar, Shape(columns, rows))
{
  this->data_buffer = (double*) new double[sizeof(double)*columns*rows]();
  this->data_size = columns*rows;
  for (int i = 0; i < columns*rows; ++i)
    this->data_buffer[i] = values[i];
}


  
double* Constant::evaluate(const Scope& scope)
{
  return this->data_buffer;
}


Constant::~Constant()
{
  delete this->data_buffer;
}

Variable::Variable(const std::string name) :
  Tensor(TensorType::Scalar,Shape()),
  name(name)
{
  
  
}


Variable::Variable(const std::string name, Shape shape) :
  Tensor(TensorType::Scalar, shape),
  name(name)
{
  
  
}

  
double* Variable::evaluate(const Scope& scope)
{
  return scope.get_variable_value(this->name);
}




Variable::~Variable ()
{

}
