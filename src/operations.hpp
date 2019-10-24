#pragma once

#include <iostream>
#include <algorithm>


#include "tensor.hpp"
#include "shape.hpp"



class Add : public Tensor
{
public:
  Add(Tensor* rhs, Tensor* lhs) :
    Tensor(TensorType::Operation),
    rhs(rhs),
    lhs(lhs)
		{
			if(rhs->shape.dim == 0 || lhs->shape.dim == 0)
			{
				const size_t new_size = std::max(lhs->get_size(),rhs->get_size());
				this->data_size = new_size;
				this->data_buffer = new double[new_size]();
				return;
			}
    
			if(rhs->shape.dim == 1 && lhs->shape.dim == 1)
			{
				if(rhs->shape.x == lhs->shape.x)
				{
					const size_t new_size = lhs->get_size();
					this->data_size = new_size;
					this->data_buffer = new double[new_size]();
					return;
				}  
			}
    
			if(rhs->shape.dim == 2 && lhs->shape.dim == 2)
			{
				if(rhs->shape.x == lhs->shape.x
					 && rhs->shape.y == lhs->shape.y)
				{
					const size_t new_size = lhs->get_size();
					this->data_size = new_size;
					this->data_buffer = new double[new_size]();
					return;
				}  
			}

			if(rhs->shape.dim == 3 && lhs->shape.dim == 3)
			{
				if(rhs->shape.x == lhs->shape.x
					 && rhs->shape.y == lhs->shape.y
					 && rhs->shape.y == lhs->shape.y)
				{
					const size_t new_size = lhs->get_size();
					this->data_size = new_size;
					this->data_buffer = new double[new_size]();
					return;
				}  
			}
			std::cout << "No, shape missmatch" << "\n";
			exit(1);
		};
  double* evaluate(const Scope& scope);  
  virtual ~Add(){}
private:
  Tensor* rhs;
  Tensor* lhs;
};

class Sub : public Tensor
{
public:
  Sub(Tensor* rhs, Tensor* lhs) :
    Tensor(TensorType::Operation),
    rhs(rhs),
    lhs(lhs)
    {
      if(rhs->shape.dim == 0 || lhs->shape.dim == 0)
      {
        const size_t new_size = std::max(lhs->get_size(),rhs->get_size());
        this->data_buffer = new double[new_size]();
        this->data_size = new_size;
        return;
      }
    
      if(rhs->shape.dim == 1 && lhs->shape.dim == 1)
      {
        if(rhs->shape.x == lhs->shape.x)
        {
          const size_t new_size = lhs->get_size();
          this->data_buffer = new double[new_size]();
          this->data_size = new_size;
          return;
        }  
      }
    
      if(rhs->shape.dim == 2 && lhs->shape.dim == 2)
      {
        if(rhs->shape.x == lhs->shape.x
           && rhs->shape.y == lhs->shape.y)
        {
          const size_t new_size = lhs->get_size();
          this->data_buffer = new double[new_size]();
          this->data_size = new_size;
          return;
        }  
      }

      if(rhs->shape.dim == 3 && lhs->shape.dim == 3)
      {
        if(rhs->shape.x == lhs->shape.x
           && rhs->shape.y == lhs->shape.y
           && rhs->shape.y == lhs->shape.y)
        {
          const size_t new_size = lhs->get_size();
          this->data_buffer = new double[new_size]();
          this->data_size = new_size;
          return;
        }  
      }
      std::cout << "No, shape missmatch" << "\n";
      exit(1);
    };
  double* evaluate(const Scope& scope);  
  virtual ~Sub(){}
private:
  Tensor* rhs;
  Tensor* lhs;
};


class Multiply : public Tensor
{
public:
  Multiply(Tensor* rhs, Tensor* lhs) :
    Tensor(TensorType::Operation),
    rhs(rhs),
    lhs(lhs)
    {
      if(rhs->shape.dim == 0 || lhs->shape.dim == 0)
      {
        const size_t new_size = std::max(lhs->get_size(),rhs->get_size());
        this->data_buffer = new double[new_size]();
        this->data_size = new_size;
        return;
      }
    
      if(rhs->shape.dim == 1 && lhs->shape.dim == 1)
      {
        if(rhs->shape.x == lhs->shape.x)
        {
          const size_t new_size = lhs->get_size();
          this->data_buffer = new double[new_size]();
          this->data_size = new_size;
          return;
        }  
      }
    
      if(rhs->shape.dim == 2 && lhs->shape.dim == 2)
      {
        if(rhs->shape.x == lhs->shape.x
           && rhs->shape.y == lhs->shape.y)
        {
          const size_t new_size = lhs->get_size();
          this->data_buffer = new double[new_size]();
          this->data_size = new_size;
          return;
        }  
      }

      if(rhs->shape.dim == 3 && lhs->shape.dim == 3)
      {
        if(rhs->shape.x == lhs->shape.x
           && rhs->shape.y == lhs->shape.y
           && rhs->shape.y == lhs->shape.y)
        {
          const size_t new_size = lhs->get_size();
          this->data_buffer = new double[new_size]();
          this->data_size = new_size;
          return;
        }  
      }
      std::cout << "No, shape missmatch" << "\n";
      exit(1);
    };
  double* evaluate(const Scope& scope);  
  virtual ~Multiply(){}
private:
  Tensor* rhs;
  Tensor* lhs;
};


class Devide : public Tensor
{
public:
  Devide(Tensor* rhs, Tensor* lhs) :
    Tensor(TensorType::Operation),
    rhs(rhs),
    lhs(lhs)
    {
      if(rhs->shape.dim == 0 || lhs->shape.dim == 0)
      {
        const size_t new_size = std::max(lhs->get_size(),rhs->get_size());
        this->data_size = new_size;
        this->data_buffer = new double[new_size]();
        return;
      }
    
      if(rhs->shape.dim == 1 && lhs->shape.dim == 1)
      {
        if(rhs->shape.x == lhs->shape.x)
        {
          const size_t new_size = lhs->get_size();
          this->data_size = new_size;
          this->data_buffer = new double[new_size]();
          return;
        }  
      }
    
      if(rhs->shape.dim == 2 && lhs->shape.dim == 2)
      {
        if(rhs->shape.x == lhs->shape.x
           && rhs->shape.y == lhs->shape.y)
        {
          const size_t new_size = lhs->get_size();
          this->data_size = new_size;
          this->data_buffer = new double[new_size]();
          return;
        }  
      }

      if(rhs->shape.dim == 3 && lhs->shape.dim == 3)
      {
        if(rhs->shape.x == lhs->shape.x
           && rhs->shape.y == lhs->shape.y
           && rhs->shape.y == lhs->shape.y)
        {
          const size_t new_size = lhs->get_size();
          this->data_size = new_size;
          this->data_buffer = new double[new_size]();
          return;
        }  
      }
      std::cout << "No, shape missmatch" << "\n";
      exit(1);
    };
  double* evaluate(const Scope& scope);  
  virtual ~Devide(){
  }
private:
  Tensor* rhs;
  Tensor* lhs;
};


class Exp : public Tensor
{
public:
  Exp(Tensor* exponent) :
    Tensor(TensorType::Operation),
    exponent(exponent)
    {
      const size_t new_size = exponent->get_size();
      this->data_size = new_size;
      this->data_buffer = new double[new_size]();
    };
  double* evaluate(const Scope& scope);  
  virtual ~Exp(){}
private:
  Tensor* exponent;
};


class Pow : public Tensor
{
public:
  Pow(Tensor* base, Tensor* exponent) :
    Tensor(TensorType::Operation),
    base(base),
    exponent(exponent)
    {

      if (exponent->shape.dim != 0)
      {
        std::cout << "No, exponent must be a scalar" << "\n";
        exit(1);
      }

      const size_t new_size = base->get_size();
      this->data_size = new_size;
      this->data_buffer = new double[new_size]();
    };
  double* evaluate(const Scope& scope);  
  virtual ~Pow(){}
private:
  Tensor* base;
  Tensor* exponent;
};


class Sum : public Tensor
{
public:
  Sum(Tensor* arr) :
    Tensor(TensorType::Operation),
    arr(arr){};
  double* evaluate(const Scope& scope);  
  virtual ~Sum(){}
private:
  Tensor* arr;
};
