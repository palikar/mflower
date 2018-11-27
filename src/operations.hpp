#pragma once
#include "tensor.hpp"




class Add : public Tensor
{
public:
  Add(Tensor* rhs, Tensor* lhs) :
    Tensor(TensorType::Operation),
    rhs(rhs),
    lhs(lhs){};
  double evaluate(const Scope& scope);  
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
    lhs(lhs){};
  double evaluate(const Scope& scope);  
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
    lhs(lhs){};
  double evaluate(const Scope& scope);  
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
    lhs(lhs){};
  double evaluate(const Scope& scope);  
  virtual ~Devide(){}
private:
  Tensor* rhs;
  Tensor* lhs;
};


class Exp : public Tensor
{
public:
  Exp(Tensor* exponent) :
    Tensor(TensorType::Operation),
    exponent(exponent){};
  double evaluate(const Scope& scope);  
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
    exponent(exponent){};
  double evaluate(const Scope& scope);  
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
  double evaluate(const Scope& scope);  
  virtual ~Sum(){}
private:
  Tensor* arr;
};



