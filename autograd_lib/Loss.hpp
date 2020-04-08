//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_LOSS_HPP
#define AUTOGRADCPP_LOSS_HPP

#include <Tensor/Tensor.hpp>

template <typename T>
class L2Loss {
public:
    Tensor<T>& forward(Tensor<T>& output, Tensor<T>& target);
    ~L2Loss();
};

template <typename T>
Tensor<T>& L2Loss<T>::forward(Tensor<T> &output, Tensor<T> &target) {
    Tensor<T>& sub = output - target;
    Tensor<T>& loss = sub * sub;
    return loss;
}

template <typename T>
L2Loss<T>::~L2Loss() {}

#endif //AUTOGRADCPP_LOSS_HPP
