//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_WEIGHTMAP_HPP
#define AUTOGRADCPP_WEIGHTMAP_HPP

#include <map>
#include <vector>
#include <Tensor/Tensor.hpp>
#include <Tensor/Matrix.hpp>

template <typename T>
class WeightMap{
public:
    std::map<std::string, Tensor<T>*> tensor; // data where it is stored
    std::map<std::string, Matrix<T>*> matrix; // data where it is stored

    WeightMap(std::vector<Tensor<T>*>& weightList);
    WeightMap(std::vector<Matrix<T>*>& weightList);
    Matrix<T>& get(std::string name);  // get matrix
    Tensor<T>& getTensor(std::string name);  // get tensor
};

template <typename T>
WeightMap<T>::WeightMap(std::vector<Tensor<T>*>& weightList){
    for(Tensor<T>* tensor : weightList){
        this->tensor.insert(std::make_pair(tensor->name, tensor));
    }
}

template <typename T>
WeightMap<T>::WeightMap(std::vector<Matrix<T>*>& weightList){
    for(Matrix<T>* matrix : weightList){
        // register matrix
        this->matrix.insert(std::make_pair(matrix->name, matrix));

        // register individual tensor
        for(int i=0;i<matrix->shape[0];i++){
            for(int j=0;j<matrix->shape[1];j++){
                Tensor<T>* temp = matrix->data[i][j];
                this->tensor.insert(std::make_pair(temp->name, temp));
            }
        }
    }
}

template <typename T>
Matrix<T>& WeightMap<T>::get(std::string name){
    Matrix<T>* matrix = nullptr;
    if(this->matrix.find(name) == this->matrix.end()){ // not found
        std::cout << "Matrix Name Not Found Error : " << name << std::endl;
        throw "Matrix Name Not Found Error";
    }else{
        matrix = this->matrix.find(name)->second;
    }
    return *matrix;
}

template <typename T>
Tensor<T>& WeightMap<T>::getTensor(std::string name){
    Tensor<T>* tensor = nullptr;
    if(this->tensor.find(name) == this->tensor.end()){ // not found
        std::cout << "Tensor Name Not Found Error : " << name << std::endl;
        throw "Tensor Name Not Found Error";
    }else{
        tensor = this->tensor.find(name)->second;
    }
    return *tensor;
}

#endif //AUTOGRADCPP_WEIGHTMAP_HPP
