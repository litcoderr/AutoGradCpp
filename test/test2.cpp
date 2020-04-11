//
// Created by litcoderr on 08/04/2020.
//
#include <iostream>
#include <Tensor/Matrix.hpp>
#include <Tensor/Tensor.hpp>

int main(){
    Matrix<double>& x = *new Matrix<double>(32, 10, 1);
    Matrix<double>& w1 = *new Matrix<double>(10, 100, 3, "W1");
    Matrix<double>& b1 = *new Matrix<double>(1, 100, 5, "B1");

    // TODO Implement Minus Operator
    // TODO Implement Back prop
    // TODO Implement Deletion
    Matrix<double>& result = x.matmul(w1) + b1.expand(32, 0);
    result.print();
    return 0;
}
