//
// Created by litcoderr on 08/04/2020.
//
#include <iostream>
#include <Tensor/Matrix.hpp>
#include <WeightMap.hpp>
#include <Loss/L2Loss.hpp>
#include <Optimizer.hpp>

Matrix<double>& graph(Matrix<double>& x, WeightMap<double>& map){
    Matrix<double>& y_ = x.matmul(map.get("W1")).matmul(map.get("W2")) + map.get("B1").expand(x.shape[0], 0);
    return y_;
}

double gt_function(double x){ // for dataset generation
    return 15 * x + 3;
}

int main(){
    Matrix<double>& w1 = *new Matrix<double>(1, 5, 1, "W1");
    Matrix<double>& w2 = *new Matrix<double>(5, 1, 1, "W2");
    Matrix<double>& b1 = *new Matrix<double>(1, 1, 1, "B1");
    // Initialize weight map
    std::vector<Matrix<double>*> weightList = {&w1, &w2, &b1};
    WeightMap<double>& weightMap = *new WeightMap<double>(weightList);
    // Initialize loss
    L2Loss<double> l2loss;  // make loss instance
    // Initialize optimizer
    double lr = 0.0001;
    Optimizer<double> optim(&weightMap, lr);

    // prepare dataset for testing
    std::vector<std::pair<double, double>> dataset;
    for(int x=-10;x<11;x++){
        dataset.push_back(std::make_pair(double(x), gt_function(double(x))));
    }

    // TODO Implement Training Sequence
    Matrix<double>& x = *new Matrix<double>(32, 1, 1);
    Matrix<double>& y = *new Matrix<double>(32, 1, 1);
    Matrix<double>& y_ = graph(x, weightMap);
    Matrix<double>& loss = l2loss.forward(y_, y);
    loss.backward();
    loss.flush();
    return 0;
}
