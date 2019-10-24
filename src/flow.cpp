#include <iostream>
#include <vector>
#include <algorithm>

#include "tensor.hpp"

int main(int argc, char* argv[])
{
    auto blk = mf::DataBlock<double>{10, 10};


    std::cout << blk.dims() << "\n";
    std::cout << blk.length() << "\n";


    std::cout << blk(5,5) << "\n";
    
    std::cout << "It works!\n";
}
