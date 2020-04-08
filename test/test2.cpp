//
// Created by litcoderr on 08/04/2020.
//
#include <iostream>
#include <Tensor/Matrix.hpp>

int main(){
    int dim1 = 3;
    int dim2 = 2;
    Matrix<double>& matrix = *new Matrix<double>(dim1, dim2, 2);

    for(int i=0;i<dim1;i++){
        for(int j=0;j<dim2;j++){
            std::cout << matrix.data[i][j]->data << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
