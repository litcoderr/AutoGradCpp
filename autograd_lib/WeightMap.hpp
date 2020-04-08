//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_WEIGHTMAP_HPP
#define AUTOGRADCPP_WEIGHTMAP_HPP

#include <map>
#include <vector>
#include <Tensor/Tensor.hpp>

template <typename T>
class WeightMap{
public:
    std::map<std::string, Tensor<T>*> data; // data where it is stored

    WeightMap(std::vector<Tensor<T>*>& weightList);
    Tensor<T>& get(std::string name);
};

template <typename T>
WeightMap<T>::WeightMap(std::vector<Tensor<T>*>& weightList){
    for(Tensor<T>* tensor : weightList){
        this->data.insert(std::make_pair(tensor->name, tensor));
    }
}

template <typename T>
Tensor<T>& WeightMap<T>::get(std::string name){
    Tensor<T>* tensor = nullptr;
    if(this->data.find(name) == this->data.end()){ // not found
        std::cout << "Weight Name Not Found Error : " << name << std::endl;
        throw "Weight Name Not Found Error";
    }else{
        tensor = this->data.find(name)->second;
    }
    return *tensor;
}

#endif //AUTOGRADCPP_WEIGHTMAP_HPP
