//
// Created by litcoderr on 08/04/2020.
//

#ifndef AUTOGRADCPP_MATRIX_HPP
#define AUTOGRADCPP_MATRIX_HPP

#include <vector>

template <template<class...> class C, typename T>
class Matrix{
public:
    int shape[2];
    std::vector<std::vector<C<T>*>> data;

    Matrix(int x, int y, T value);  // used for initialization
    Matrix(int x, int y, T value, std::string name);  // used for initialization
    Matrix(std::vector<std::vector<C<T>*>>& data);  // for existing tensor

    void print();
};

template <template<class...> class C, typename T>
Matrix<C, T>::Matrix(int x, int y, T value): Matrix(x, y, value, "") {}


template <template<class...> class C, typename T>
Matrix<C, T>::Matrix(int x, int y, T value, std::string name) {
    this->shape[0] = x;
    this->shape[1] = y;
    for(int i=0; i<this->shape[0]; i++){
        std::vector<C<T>*>* temp_vec = new std::vector<C<T>*>;
        for(int j=0; j<this->shape[1]; j++){
            std::string temp_name = name;
            temp_name.append("_").append(std::to_string(i)).append("_").append(std::to_string(j));
            C<T>& temp_tensor = *new C<T>(value, temp_name);
            temp_vec->push_back(&temp_tensor);
        }
        this->data.push_back(*temp_vec);
    }
}

template <template<class...> class C, typename T>
Matrix<C, T>::Matrix(std::vector<std::vector<C<T>*>>& data){
    this->data = data;
    this->shape[0] = this->data.size();
    this->shape[1] = this->data[0].size();
}

template <template<class...> class C, typename T>
void Matrix<C, T>::print(){
    std::cout << "-------\n";
    for(int i=0;i<this->shape[0];i++){
        for(int j=0;j<this->shape[1];j++){
            std::cout << this->data[i][j]->data << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------\n";
}

#endif //AUTOGRADCPP_MATRIX_HPP
