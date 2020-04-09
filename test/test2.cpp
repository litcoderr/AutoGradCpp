//
// Created by litcoderr on 08/04/2020.
//
#include <iostream>
#include <Tensor/Matrix.hpp>
#include <Tensor/Tensor.hpp>

int main(){
    Matrix<double>& x = *new Matrix<double>(3, 3, 1);
    Matrix<double>& w = *new Matrix<double>(3, 3, 1, "Weight");

    // TODO Implement Operators
    // TODO Implement Deletion
    Matrix<double>& result = w + x;

    return 0;
}
