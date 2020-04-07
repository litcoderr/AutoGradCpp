//
// Created by litcoderr on 07/04/2020.
//

#ifndef AUTOGRADCPP_TENSOR_HPP
#define AUTOGRADCPP_TENSOR_HPP

#include "../GraphNode/GraphNode.hpp"

template <typename T>
class Tensor {
public:
    T data;
    T grad;
    bool valid_grad;

    Tensor();
    Tensor(T data);

    // Operator Overloading -> Conversion to GraphNode
    // Addition
    friend GraphNode<T>& operator+(const GraphNode<T> &, const Tensor<T> &);
    friend GraphNode<T>& operator+(const Tensor<T> &, const GraphNode<T> &);
    friend GraphNode<T>& operator+(const Tensor<T> &, const Tensor<T> &);
};

template <typename T>
Tensor<T>::Tensor() {
    this->data = 0;
    this->grad = 0;
    this->valid_grad = false;
}

template <typename T>
Tensor<T>::Tensor(T data) {
    this->data = data;
    this->grad = 0;
    this->valid_grad = false;
}

// Operator Overloading -> Conversion to GraphNode
// Addition
template <typename T>
GraphNode<T>& operator+(const GraphNode<T> & leftNode, const Tensor<T> & rightTensor){
    GraphNode<T>& rightNode = new GraphNode<T>(&rightTensor);
    GraphNode<T>& nextNode = leftNode + rightNode;
    return nextNode;
}

template <typename T>
GraphNode<T>& operator+(const Tensor<T> & leftTensor, const GraphNode<T> & rightNode){
    GraphNode<T>& leftNode = new GraphNode<T>(&leftTensor);
    GraphNode<T>& nextNode = leftNode + rightNode;
    return nextNode;
}

template <typename T>
GraphNode<T>& operator+(const Tensor<T> & leftTensor, const Tensor<T> & rightTensor){
    GraphNode<T>& leftNode = new GraphNode<T>(&leftTensor);
    GraphNode<T>& rightNode = new GraphNode<T>(&rightTensor);
    GraphNode<T>& nextNode = leftNode + rightNode;
    return nextNode;
}

#endif //AUTOGRADCPP_TENSOR_HPP
