#include <iostream>
#include "tensor.hpp"
#include "operations.hpp"
#include <vector>
#include <algorithm>




int main(int argc, char* argv[])
{

    Scope default_scope;
    Tensor *x = default_scope.new_variable("x", 10.0);

    std::vector<double> aa = { 3, 4 };
    std::vector<double> bb = { 5, 6 };


    Tensor *a = new Constant(10);
    Tensor *b = new Constant(aa);


    std::vector<std::string> strs;


    Tensor *sum = new Add(a, b);


    TensorArray *ar = new TensorArray(ArrayType::Scalar);

    ar->add_tensor(a);
    ar->add_tensor(b);
    ar->add_tensor(sum);

    Tensor *res = new Sum(ar);

    res = new Devide(new Sub(new Multiply(sum, a), a), x);

    std::cout << *res->evaluate(default_scope) << "\n";

    std::cout << "It works!"
              << "\n";
}
