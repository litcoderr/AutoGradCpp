//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_OPTIMIZER_HPP
#define AUTOGRADCPP_OPTIMIZER_HPP

#include <Tensor.hpp>
#include <vector>
#include <map>

template <typename T>
class Optimizer {
public:
    float lr; // learning rate
    std::map<std::string, Tensor<T>*>* weights;  // weights
    Optimizer(std::map<std::string, Tensor<T>*>* weights, float lr);

    void step();
};

template <typename T>
Optimizer<T>::Optimizer(std::map<std::string, Tensor<T>*>* weights, float lr){
    this->lr = lr;
    this->weights = weights;
}

template <typename T>
void Optimizer<T>::step() {
    for(typename std::map<std::string,Tensor<T>*>::iterator it=this->weights->begin(); it!=this->weights->end(); it++){
        it->second->data -= this->lr * it->second->grad;
        it->second->grad = 0; // Initialize gradient to 0
    }
}

#endif //AUTOGRADCPP_OPTIMIZER_HPP
