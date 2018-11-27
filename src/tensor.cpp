#include "tensor.hpp"
#include <iostream>




Scope::Scope()
{
  
}


double Scope::get_variable_value(const std::string& name) const
{
  if (this->variables.count(name)) {
    return this->variables.at(name);
  }
  std::cout << "No variable named " << name << "\n";
  exit(1);
  return 0;
}

Variable* Scope::new_variable(const std::string& name, double default_value)
{
  Variable* new_var = new Variable(name);
  this->variables[name] = default_value;
  return new_var;
}
  
Scope::~Scope()
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
  Tensor(TensorType::Array),
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

Constant::Constant(double value): Tensor(TensorType::Scalar), value(value)
{
  
}
  
double Constant::evaluate(const Scope& scope)
{
  return this->value;

}


Constant::~Constant()
{

}

Variable::Variable(const std::string name) :Tensor(TensorType::Scalar), name(name)
{
  
  
}
  
double Variable::evaluate(const Scope& scope)
{
  return scope.get_variable_value(this->name);
}




Variable::~Variable ()
{

}
