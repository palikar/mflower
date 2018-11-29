#include <iostream>


#include "tensor.hpp"

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




