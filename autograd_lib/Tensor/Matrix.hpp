//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_MATRIX_HPP
#define AUTOGRADCPP_MATRIX_HPP

#include <vector>
#include <Tensor/Tensor.hpp>

template <typename T>
class Matrix{
public:
    int shape[2];
    bool isVariable;
    std::vector<std::vector<Tensor<T>*>> data;

    Matrix(int x, int y, T value);  // used for initialization
    Matrix(int x, int y, T value, std::string name, bool isVariable = true);  // used for initialization
    Matrix(std::vector<std::vector<Tensor<T>*>>& data);  // for existing tensor

    void print();
    bool isSameShape(Matrix<T>& operand);

    // Operator
    Matrix<T>& operator+(Matrix<T>& operand);  // element-wise Addition
    Matrix<T>& operator*(Matrix<T>& operand);  // element-wise Multiplication
    Matrix<T>& matmul(Matrix<T>& operand);
    Matrix<T>& add(Matrix<T>& operand, int axis = 0);  // axis-wise Addition
};

template <typename T>
Matrix<T>::Matrix(int x, int y, T value): Matrix(x, y, value, "", false) {} // for plain Tensors

template <typename T>
Matrix<T>::Matrix(int x, int y, T value, std::string name, bool isVariable) {  // for Variable
    this->shape[0] = x;
    this->shape[1] = y;
    this->isVariable = isVariable;
    for(int i=0; i<this->shape[0]; i++){
        std::vector<Tensor<T>*> temp_vec;
        for(int j=0; j<this->shape[1]; j++){
            std::string temp_name = name;
            temp_name.append("_").append(std::to_string(i)).append("_").append(std::to_string(j));
            if(isVariable){
                Variable<T>& temp_tensor = *new Variable<T>(value, temp_name);
                temp_vec.push_back(&temp_tensor);
            }else{
                Tensor<T>& temp_tensor = *new Tensor<T>(value, temp_name);
                temp_vec.push_back(&temp_tensor);
            }
        }
        this->data.push_back(temp_vec);
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<Tensor<T>*>>& data){
    this->data = data;
    this->shape[0] = this->data.size();
    this->shape[1] = this->data[0].size();
}

template <typename T>
void Matrix<T>::print(){
    std::cout << "-------\n";
    for(int i=0;i<this->shape[0];i++){
        for(int j=0;j<this->shape[1];j++){
            std::cout << this->data[i][j]->data << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------\n";
}

template <typename T>
bool Matrix<T>::isSameShape(Matrix<T> & operand) {
    return this->shape[0] == operand.shape[0] && this->shape[1] == operand.shape[1];
}

template <typename T>
Matrix<T>& Matrix<T>::operator+(Matrix<T>& operand){
    std::vector<std::vector<Tensor<T>*>> vec2d;

    if(this->isSameShape(operand)){
        for(int i=0; i<this->shape[0]; i++){
            std::vector<Tensor<T>*> vec1d;
            for(int j=0; j<this->shape[1]; j++){
                Tensor<T>& temp_tensor = *this->data[i][j] + *operand.data[i][j];
                vec1d.push_back(&temp_tensor);
            }
            vec2d.push_back(vec1d);
        }
    }else{
        std::cout << "Shape Mismatch. [" << this->shape[0] << ", " << this->shape[1] << "] <--> [" << operand.shape[0] << ", " << operand.shape[1] << "]" << std::endl;
        throw;
    }

    Matrix<T>& resultMatrix = *new Matrix<T>(vec2d);
    return resultMatrix;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*(Matrix<T> & operand) {
    std::vector<std::vector<Tensor<T>*>> vec2d;
    if(this->isSameShape(operand)){
        for(int i=0; i<this->shape[0]; i++){
            std::vector<Tensor<T>*> vec1d;
            for(int j=0; j<this->shape[1]; j++){
                Tensor<T>& temp_tensor = *this->data[i][j] * *operand.data[i][j];
                vec1d.push_back(&temp_tensor);
            }
            vec2d.push_back(vec1d);
        }
    }else{
        std::cout << "Shape Mismatch. [" << this->shape[0] << ", " << this->shape[1] << "] <--> [" << operand.shape[0] << ", " << operand.shape[1] << "]" << std::endl;
        throw;
    }
    Matrix<T>& resultMatrix = *new Matrix<T>(vec2d);
    return resultMatrix;
}

template <typename T>
Matrix<T>& Matrix<T>::matmul(Matrix<T>& operand){
    std::vector<std::vector<Tensor<T>*>> vec2d;
    int dim1 = this->shape[0];
    int dim2 = operand.shape[1];
    if(this->shape[1] == operand.shape[0]){
        for(int i=0;i<dim1;i++){
            std::vector<Tensor<T>*> vec1d;
            for(int j=0;j<dim2;j++){
                Tensor<T>* newTensor = new Tensor<T>;
                for(int k=0;k<this->shape[1];k++){
                    Tensor<T>& mulTensor = *this->data[i][k] * *(operand.data[k][j]);
                    newTensor = &(*newTensor + mulTensor);
                }
                vec1d.push_back(newTensor);
            }
            vec2d.push_back(vec1d);
        }
    }else{
        std::cout << "MatMul Shape Mismatch. [" << this->shape[0] << ", " << this->shape[1] << "] <--> [" << operand.shape[0] << ", " << operand.shape[1] << "]" << std::endl;
        throw;
    }
    Matrix<T>& resultMatrix = *new Matrix<T>(vec2d);
    return resultMatrix;
}

template <typename T>
Matrix<T>& Matrix<T>::add(Matrix<T> & operand, int axis) {
    // expand by axis
    int vec_axis = (axis==1)? 0 : 1;
    std::vector<std::vector<Tensor<T>*>> vec2d;
    if(operand.shape[axis]==1 && operand.shape[vec_axis] == this->shape[vec_axis]){
        //TODO Implement extended addition
    }else{
        std::cout << "Axis: " << axis << " Addition Shape Mismatch. [" << this->shape[0] << ", " << this->shape[1] << "] <--> [" << operand.shape[0] << ", " << operand.shape[1] << "]" << std::endl;
        throw;
    }
    Matrix<T>& resultMatrix = *new Matrix<T>(vec2d);
    return resultMatrix;
}

#endif //AUTOGRADCPP_MATRIX_HPP
