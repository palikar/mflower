#include <iostream>
#include <vector>
#include <algorithm>

#include "tensor.hpp"

int main(int, char**)
{



    auto blk = mf::DataBlock<double>{{1,3,4}};


    std::cout << blk.dims() << "\n";
    std::cout << blk.length() << "\n";
    std::cout << blk(1, 2, 3) << "\n";


    auto tens = mf::Tensor("init");

    // double vals_1[] = {1.0, 2.0, 3.0};

    double vals_2[3][3] = {{1.0, 2.0, 3.0},
                           {4.0, 5.0, 6.0},
                           {9.0, 8.0, 7.0}};

    tens.init_data(vals_2);

    std::cout << "----------------" << "\n";

    std::cout << tens.data(1,1) << "\n";
    
    std::cout << "It works!\n";
}
