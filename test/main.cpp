//
// Created by litcoderr on 07/04/2020.
//

#include <iostream>
#include <map>
#include <string>
#include <Tensor.hpp>
#include <Optimizer.hpp>

Tensor<float>& model(Tensor<float>& input, std::map<std::string, Tensor<float>*>& weights){
    // Dynamic Graph of Y = W*X+B
    Tensor<float>& output = *weights.find("Weight")->second * input + *weights.find("Bias")->second;
    return output;
}

int main(){
    //TODO Need Memory Deletion process
    //Initialize Weights
    Tensor<float>& weight = *new Tensor<float>(2);
    Tensor<float>& bias = *new Tensor<float>(3);
    //Initialize WeightMap
    std::map<std::string, Tensor<float>*> weightMap;
    weightMap.insert(std::make_pair("Weight", &weight));
    weightMap.insert(std::make_pair("Bias", &bias));
    //Initialize Optimizer
    float learning_rate = 0.001;
    Optimizer<float> optim(&weightMap, learning_rate);

    //Compute Through dynamic graph
    Tensor<float>& input = *new Tensor<float>(5);
    Tensor<float>& result = model(input, weightMap);

    //BackPropagate
    result.backward();

    //Step
    optim.step();
    return 0;
}
