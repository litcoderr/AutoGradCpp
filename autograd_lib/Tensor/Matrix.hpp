//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_MATRIX_HPP
#define AUTOGRADCPP_MATRIX_HPP

#include <Tensor/Tensor.hpp>
#include <vector>

template <typename T>
class Matrix{
public:
    int shape[2];
    std::vector<std::vector<Tensor<T>*>> data;

    Matrix(int x, int y, T value);  // used for initialization
};

template <typename T>
Matrix<T>::Matrix(int x, int y, T value) {
    this->shape[0] = x;
    this->shape[1] = y;
    for(int i=0; i<x; i++){
        std::vector<Tensor<T>*>* temp_vec = new std::vector<Tensor<T>*>;
        for(int j=0; j<y; j++){
            Tensor<T>& temp_tensor = *new Tensor<T>(value);
            temp_vec->push_back(&temp_tensor);
        }
        this->data.push_back(*temp_vec);
    }
}

#endif //AUTOGRADCPP_MATRIX_HPP
