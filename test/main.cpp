//
// Created by litcoderr on 07/04/2020.
//

#include <iostream>
#include <Tensor.hpp>

int main(){
    Tensor<float>& a = *new Tensor<float>(1);
    Tensor<float>& b = *new Tensor<float>(2);
    Tensor<float>& dynamic_graph  = a*a + b*b;
    dynamic_graph.backward();

    std::cout << dynamic_graph.data << std::endl;
    std::cout << a.grad << std::endl;
    return 0;
}
