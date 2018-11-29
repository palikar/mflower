#include <cmath>
#include <iostream>

#include "operations.hpp"



double* Add::evaluate(const Scope& scope)
{
  double* lhs_data = lhs->evaluate(scope);
  double* rhs_data = rhs->evaluate(scope);


  
  size_t rhs_size = rhs->get_size();
  size_t lhs_size = lhs->get_size();
    
  if (lhs_size == 1)
  {
    
  
    for(size_t i = 0 ; i < rhs_size; i++)
      this->data_buffer[i] = *lhs_data + rhs_data[i];
  }
  else if (rhs_size == 1)
  {
    for(size_t i = 0;i < lhs_size;i++)
      this->data_buffer[i] = *rhs_data + lhs_data[i];
  }
  else
  {
    for(size_t i = 0;i<lhs_size;i++)
      this->data_buffer[i] = rhs_data[i] + lhs_data[i];
  }
  
  
  return this->data_buffer;
}


double* Sub::evaluate(const Scope& scope)
{
  double* lhs_data = lhs->evaluate(scope);
  double* rhs_data = rhs->evaluate(scope);

  size_t rhs_size = rhs->get_size();
  size_t lhs_size = lhs->get_size();

  if (lhs_size == 1)
  {
    for(size_t i = 0;i<rhs_size;i++)
      this->data_buffer[i] = rhs_data[i] - *lhs_data ;
  }
  else if (rhs_size == 1)
  {
    for(size_t i = 0;i<lhs_size;i++)
      this->data_buffer[i] =  lhs_data[i] - *rhs_data;
  }
  else
  {
    for(size_t i = 0;i<lhs_size;i++)
      this->data_buffer[i] =  lhs_data[i] - rhs_data[i];
  }
  
  
  return this->data_buffer;
}


double* Multiply::evaluate(const Scope& scope)
{
  
  double* lhs_data = lhs->evaluate(scope);
  double* rhs_data = rhs->evaluate(scope);

  size_t rhs_size = rhs->get_size();
  size_t lhs_size = lhs->get_size();

  if (lhs_size == 1)
  {
    for(size_t i = 0;i<rhs_size;i++)
      this->data_buffer[i] = *lhs_data * rhs_data[i];
  }
  else if (rhs_size == 1)
  {
    for(size_t i = 0;i<lhs_size;i++)
      this->data_buffer[i] = *rhs_data * lhs_data[i];
  }
  else
  {
    for(size_t i = 0;i<lhs_size;i++)
      this->data_buffer[i] = rhs_data[i] * lhs_data[i];
  }
  
  
  return this->data_buffer;

}


double* Devide::evaluate(const Scope& scope)
{
  
  
  double* lhs_data = lhs->evaluate(scope);
  double* rhs_data = rhs->evaluate(scope);

  size_t rhs_size = rhs->get_size();
  size_t lhs_size = lhs->get_size();

  if (lhs_size == 1)
  {
    for(size_t i = 0;i<rhs_size;i++)
      this->data_buffer[i] = rhs_data[i] / *lhs_data;
  }
  else if (rhs_size == 1)
  {
    for(size_t i = 0;i<lhs_size;i++)
      this->data_buffer[i] = lhs_data[i] / *rhs_data;
  }
  else
  {
    for(size_t i = 0;i < lhs_size;i++)
      this->data_buffer[i] = lhs_data[i] / *lhs_data;
  }
  
  
  return this->data_buffer;


}



double* Exp::evaluate(const Scope& scope)
{
  const double* data = this->exponent->evaluate(scope);
  const size_t size = this->exponent->get_size();
  
  for(size_t i = 0; i<size; i++)
    this->data_buffer[i] = std::exp(data[i]);
  
  return this->data_buffer;
}


double* Pow::evaluate(const Scope& scope)
{
    const double* data = this->exponent->evaluate(scope);
    const size_t size = this->exponent->get_size();
    const double* base_data = this->base->evaluate(scope);


    for(size_t i = 0; i<size; i++)
      this->data_buffer[i] = std::pow(*base_data, data[i]);
  
  return this->data_buffer;
}


double* Sum::evaluate(const Scope& scope)
{
  // if (arr->type != TensorType::Array){
  //   std::cout << "Coont sum over non-array!" << "\n";
  //   exit(1);
  // }
  // double sum = 0;
  // TensorArray* ta = (TensorArray*)arr;
  // for (const auto& t : ta->get_elements())
  // {
  //   sum += t->evaluate(scope);
  // }
  
  return this->data_buffer;
}
