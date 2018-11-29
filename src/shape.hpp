#pragma once

class Shape
{
public:
  Shape():
    x(-1),
    y(-1),
    z(-1),
    dim(0)
    {};
  Shape(int i):
    x(i),
    y(-1),
    z(-1),
    dim(1)
    {};
  Shape(int i, int j):
    x(i),
    y(j),
    z(-1),
    dim(1)
    {};
  Shape(int i, int j, int k):
    x(i),
    y(j),
    z(k),
    dim(1)
    {};
  
  virtual ~Shape(){};
  
  int dim;
  int x;
  int y;
  int z;
private:
};
