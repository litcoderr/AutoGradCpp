//
// Created by litcoderr on 08/04/2020.
//
#include <iostream>
#include <Tensor/Matrix.hpp>
#include <Tensor/Tensor.hpp>

int main(){
    Matrix<Tensor, double>& x = *new Matrix<Tensor, double>(1, 3, 1);
    Matrix<Variable, double>& w = *new Matrix<Variable, double>(3, 2, 1, "W");

    // TODO Implement Operators
    // TODO Implement Deletion
    w.print();
    return 0;
}
