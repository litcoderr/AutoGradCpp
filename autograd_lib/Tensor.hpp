//
// Created by litcoderr on 07/04/2020.
//

#ifndef AUTOGRADCPP_TENSOR_HPP
#define AUTOGRADCPP_TENSOR_HPP

#include <stack>
template <typename T> class Tensor;
template <typename T> class Heading;

enum Operator{
    NO_OP,
    ADD,
    SUBTRACT,
    MULTIPLY
};

template<typename T>
T compute_grad(Heading<T>* heading, T prev_grad){
    Operator op = heading->op;
    if(op == ADD){
        return prev_grad;
    }else if(op == SUBTRACT){
        return prev_grad;
    }else if(op == MULTIPLY){
        return prev_grad * heading->adj->data * prev_grad;
    }else {
        return 0;
    }
}

template <typename T>
class Heading{
public:
    Tensor<T>* from; // from which Tensor Node
    Tensor<T>* adj;  // Adjacent Heading Tensor Node
    Tensor<T>* to; // Parent Heading Tensor Node
    Operator op; // Heading Operation

    Heading(Tensor<T>* from, Tensor<T>* adj, Tensor<T>* parent, Operator op);
};

template <typename T>
class Tensor{
public:
    T data;  // data
    T grad;  // gradient
    bool is_varialbe;
    std::stack<Heading<T>*> op_stack; // head

    Tensor(); // Variable
    Tensor(T data);  // Variable
    Tensor(T data, bool is_variable);
    ~Tensor();

    void backward();  // default backward called from head node
    void backward(T prev_grad);
    void flush();  // clear all memory

    // Operator Overloading
    Tensor<T>& operator+(Tensor<T>& operand);  // Addition
    Tensor<T>& operator-(Tensor<T>& operand);  // Subtraction
    Tensor<T>& operator*(Tensor<T>& operand);  // Multiplication
};

template <typename T>
Heading<T>::Heading(Tensor<T>* from, Tensor<T>* adj, Tensor<T>* parent, Operator op) {
    this->from = from;
    this->adj = adj;
    this->to = to;
    this->op = op;
}

// Tensor Definition
template <typename T>
Tensor<T>::Tensor() : Tensor(0, true){}

template <typename T>
Tensor<T>::Tensor(T data) : Tensor(data, true){}

template <typename T>
Tensor<T>::Tensor(T data, bool is_variable){
    this->data = data;
    this->grad = 0;
    this->is_varialbe = is_variable;
}

template<typename T>
Tensor<T>::~Tensor(){
    while(!this->op_stack.empty()){
        delete this->op_stack.top();
        this->op_stack.pop();
    }
}

template <typename T>
void Tensor<T>::backward() {
    this->backward(1);  // default gradient is 1
}

template <typename T>
void Tensor<T>::backward(T grad){
    this->grad += grad; // update this gradient
    while(!this->op_stack.empty()){  // propagate through ops
        Heading<T>* heading = this->op_stack.top();
        T child_gradient = compute_grad(heading, grad);
        heading->from->backward(child_gradient);
        this->op_stack.pop();
    }
}

template <typename T>
void Tensor<T>::flush() {
    while(!this->op_stack.empty()){
        Heading<T>* heading = this->op_stack.top();
        heading->from->flush();
    }
    delete this;
}

// Operator Overloading
template <typename T>
Tensor<T>& Tensor<T>::operator+(Tensor<T> & operand) {
    Tensor<T>* nextTensor = new Tensor<T>(this->data+operand.data, false);
    Heading<T>* head_1 = new Heading<T>(this, &operand, nextTensor, ADD);
    Heading<T>* head_2 = new Heading<T>(&operand, this, nextTensor, ADD);

    nextTensor->op_stack.push(head_1);
    nextTensor->op_stack.push(head_2);

    return *nextTensor;
}

template <typename T>
Tensor<T>& Tensor<T>::operator-(Tensor<T> & operand) {
    Tensor<T>* nextTensor = new Tensor<T>(this->data-operand.data, false);
    Heading<T>* head_1 = new Heading<T>(this, &operand, nextTensor, SUBTRACT);
    Heading<T>* head_2 = new Heading<T>(&operand, this, nextTensor, SUBTRACT);

    nextTensor->op_stack.push(head_1);
    nextTensor->op_stack.push(head_2);

    return *nextTensor;
}

template <typename T>
Tensor<T>& Tensor<T>::operator*(Tensor<T> & operand) {
    Tensor<T>* nextTensor = new Tensor<T>(this->data*operand.data, false);
    Heading<T>* head_1 = new Heading<T>(this, &operand, nextTensor, MULTIPLY);
    Heading<T>* head_2 = new Heading<T>(&operand, this, nextTensor, MULTIPLY);

    nextTensor->op_stack.push(head_1);
    nextTensor->op_stack.push(head_2);

    return *nextTensor;
}

#endif //AUTOGRADCPP_TENSOR_HPP
