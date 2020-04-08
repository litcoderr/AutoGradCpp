//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_OPTIMIZER_HPP
#define AUTOGRADCPP_OPTIMIZER_HPP

#include <Tensor.hpp>
#include <vector>
#include <WeightMap.hpp>

template <typename T>
class Optimizer {
public:
    T lr; // learning rate
    WeightMap<T>* weights;  // weights
    Optimizer(WeightMap<T>* weights, T lr);

    void step();
};

template <typename T>
Optimizer<T>::Optimizer(WeightMap<T>* weights, T lr){
    this->lr = lr;
    this->weights = weights;
}

template <typename T>
void Optimizer<T>::step() {
    for(typename std::map<std::string,Tensor<T>*>::iterator it=this->weights->data.begin(); it!=this->weights->data.end(); it++){
        Tensor<T>* currentTensor = it->second;
        currentTensor->data -= this->lr * currentTensor->grad;
        currentTensor->grad = 0; // Initialize gradient to 0
    }
}

#endif //AUTOGRADCPP_OPTIMIZER_HPP
