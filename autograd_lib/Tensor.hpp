//
// Created by litcoderr on 07/04/2020.
//

#ifndef AUTOGRADCPP_TENSOR_HPP
#define AUTOGRADCPP_TENSOR_HPP

#include <stack>
#include <Operator.hpp>
template <typename T> class Tensor;
template <typename T> class Heading;

template <typename T>
class Heading{
public:
    Tensor<T>* adj;  // Adjacent Heading Tensor Node
    Tensor<T>* parent; // Parent Heading Tensor Node
    Operator op; // Heading Operation

    Heading(Tensor<T>* adj, Tensor<T>* parent, Operator op);
};

template <typename T>
class Tensor{
public:
    T data;  // data
    T grad;  // gradient
    std::stack<Heading<T>> from; // head

    Tensor();
    Tensor(T data);

    // Operator Overloading
    Tensor<T>& operator+(Tensor<T>& operand);  // Addition
};

template <typename T>
Heading<T>::Heading(Tensor<T>* adj, Tensor<T>* parent, Operator op) {
    this->adj = adj;
    this->parent = parent;
    this->op = op;
}

// Tensor Definition
template <typename T>
Tensor<T>::Tensor(){
    this->data = 0;
    this->grad = 0;
}

template <typename T>
Tensor<T>::Tensor(T data){
    this->data = data;
    this->grad = 0;
}

// Operator Overloading
template <typename T>
Tensor<T>& Tensor<T>::operator+(Tensor<T> & operand) {
    Tensor<T>* nextTensor = new Tensor<T>(this->data+operand.data);
    return *nextTensor;
}

#endif //AUTOGRADCPP_TENSOR_HPP
