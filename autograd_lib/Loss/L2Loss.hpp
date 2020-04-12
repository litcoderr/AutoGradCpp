//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_L2LOSS_HPP
#define AUTOGRADCPP_L2LOSS_HPP

#include <Tensor/Tensor.hpp>
#include <Tensor/Matrix.hpp>

template <typename T>
class SquaredDiff {
public:
    Tensor<T>& forward(Tensor<T>& output, Tensor<T>& target);
};

template <typename T>
class L2Loss {
public:
    SquaredDiff<T> diff;
    Matrix<T>& forward(Matrix<T>& output, Matrix<T>& target);
};

template <typename T>
Tensor<T>& SquaredDiff<T>::forward(Tensor<T> &output, Tensor<T> &target) {
    Tensor<T>& sub = output - target;
    Tensor<T>& loss = sub * sub;
    return loss;
}

template <typename T>
Matrix<T>& L2Loss<T>::forward(Matrix<T> & output, Matrix<T> & target) {
    Matrix<T>& resultMatrix = *new Matrix<double>(1, 1, 0);
    if(!output.isSameShape(target)){
        std::cout << "Shape Mismatch L2Loss." << std::endl;
        throw;
    }else{
        Tensor<double>* total_loss = new Tensor<double>();
        for(int i=0;i<output.shape[0];i++){
            for(int j=0;j<output.shape[1];j++){
                total_loss = &(*total_loss + this->diff.forward(*output.data[i][j], *target.data[i][j]));
            }
        }
        delete resultMatrix.data[0][0];
        resultMatrix.data[0][0] = total_loss;
    }
    return resultMatrix;
}

#endif //AUTOGRADCPP_L2LOSS_HPP
