//
// Created by litcoderr on 07/04/2020.
//

#ifndef AUTOGRADCPP_GRAPHNODE_HPP
#define AUTOGRADCPP_GRAPHNODE_HPP

#include "../Operator/Operator.hpp"
#include "../Tensor/Tensor.hpp"

template <typename T>
class GraphNode {
public:
    Tensor<T>* tensor;
    GraphNode<T>* adjacent;
    GraphNode<T>* leftChild;
    GraphNode<T>* rightChild;
    GraphNode<T>* parent;
    Operator op;  // operation type

    GraphNode(); // Newly Created
    GraphNode(Tensor<T>* tensor);  // Existing tensors

    // operator overloading
    GraphNode<T>& operator+(const GraphNode<T>&) const;
};

template <typename T>  // Newly Created
GraphNode<T>::GraphNode() {
    this->tensor = new Tensor<T>();
    this->op = NO_OP;
    this->adjacent = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->parent = nullptr;
}

template <typename T>  // Existing Tensor
GraphNode<T>::GraphNode(Tensor<T>* tensor) {
    this->tensor = tensor;
    this->op = NO_OP;
    this->adjacent = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->parent = nullptr;
}

//Operator Overloading
// Addition
template <typename T>
GraphNode<T>& GraphNode<T>::operator+(const GraphNode<T>& input)const {
    GraphNode<T> parentNode = new GraphNode<T>();  // new parent node

    //update parent Node
    parentNode.tensor->data = this->tensor->data + input.tensor->data;
    parentNode.leftChild = this;
    parentNode.rightChild = &input;

    //update this Node
    this->op = ADD;
    this->adjacent = &input;
    this->parent = &parentNode;

    //update input Node
    input.op = ADD;
    input.adjacent = this;
    input.parent = &parentNode;

    return parentNode;
}

#endif //AUTOGRADCPP_GRAPHNODE_HPP
