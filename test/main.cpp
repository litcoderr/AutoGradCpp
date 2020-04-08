//
// Created by litcoderr on 07/04/2020.
//

#include <iostream>
#include <Tensor.hpp>

int main(){
    Tensor<float>* a = new Tensor<float>(3.1);
    Tensor<float>* b = new Tensor<float>(2.5);
    Tensor<float>& c = *a + (*a + *b);
    return 0;
}
