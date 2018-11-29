#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "shape.hpp"


class Variable;
class Scope
{
public:
  Scope();
  double get_variable_value(const std::string& name) const;

  Variable* new_variable(const std::string& name, double default_value);
  Variable* new_variable(const std::string& name, std::vector<double> default_value);
  Variable* new_variable(const std::string& name, Shape shape);
  
  virtual ~Scope();
private:
  std::unordered_map<std::string, double*> variables;  
};


enum class TensorType {
  Scalar,
  Matrix,
  Array,
  Operation
};

enum class ArrayType {
  Scalar,
  Matrix
};

class Tensor
{
public:
  Tensor(const TensorType type, const Shape shape);
  Tensor(const TensorType type);

  virtual double evaluate(const Scope& scope) = 0;
  virtual ~Tensor();
  TensorType type;
  Shape shape;
private:
};


class TensorArray : public Tensor
{
public:
  TensorArray(ArrayType type);

  virtual double evaluate(const Scope& scope);
  void add_tensor(Tensor* t);
  std::vector<Tensor*>& get_elements();
  virtual ~TensorArray();
  ArrayType arr_type;
private:
  std::vector<Tensor*> tensors;
};



class Constant : public Tensor
{
public:
  Constant(double value);
  Constant(std::vector<double> values);
  
  double evaluate(const Scope& scope);
  virtual ~Constant();
private:
  double value;
};


class Variable : public Tensor
{
public:
  Variable(const std::string name);
  
  double evaluate(const Scope& scope);
  virtual ~Variable ();
private:
  std::string name;
};


