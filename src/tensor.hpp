#pragma once
#include <string>
#include <vector>
#include <unordered_map>


class Variable;

class Scope
{
public:
  Scope();
  double get_variable_value(const std::string& name) const;
  Variable* new_variable(const std::string& name, double default_value);
  
  virtual ~Scope();
private:
  std::unordered_map<std::string, double> variables;  
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
  Tensor(const TensorType type);

  virtual double evaluate(const Scope& scope) = 0;
  virtual ~Tensor();
  TensorType type;
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


