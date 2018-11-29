#include <iostream>


#include "tensor.hpp"

Scope::Scope()
{
  
}

double* Scope::get_variable_value(const std::string& name) const
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
  Variable* new_var = new Variable(name, Shape());
  this->variables[name] = (double*) new(double);
  *this->variables[name] = default_value;
  return new_var;
}


Variable* Scope::new_variable(const std::string& name, std::vector<double> default_value)
{
  Variable* new_var = new Variable(name, Shape(default_value.size()));
  this->variables[name] = (double*) new double[sizeof(double)*default_value.size()]();

  size_t index = 0;

  for (auto& val : default_value)
    this->variables[name][index++] = val;
  
  return new_var;
}


Variable* Scope::new_variable(const std::string& name, Shape shape)
{
  Variable* new_var = new Variable(name,shape);

  int num = 1;
  if (shape.x >= 1)
    num *= shape.x;
  if (shape.y >= 1)
    num *= shape.x;
  if (shape.z >= 1)
    num *= shape.x;

  this->variables[name] = (double*) new(double);
  this->variables[name] = new double[num]();
  return new_var;
}


  
Scope::~Scope()
{

}




