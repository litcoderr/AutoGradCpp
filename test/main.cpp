//
// Created by litcoderr on 07/04/2020.
//

#include <iostream>
#include <vector>
#include <Tensor.hpp>
#include <WeightMap.hpp>
#include <Optimizer.hpp>

Tensor<float>& model(Tensor<float>& input, WeightMap<float>& weights){
    // Dynamic Graph of Y = W*X+B
    Tensor<float>& output = weights.get("Weight") * input + weights.get("Bias");
    return output;
}

int main(){
    //TODO Tensor / Variable
    //Initialize Weights
    Tensor<float>& weight = *new Tensor<float>(2, "Weight");
    Tensor<float>& bias = *new Tensor<float>(3, "Bias");
    //Initialize WeightMap
    std::vector<Tensor<float>*> weightList = {&weight, &bias};
    WeightMap<float>& weightMap = *new WeightMap<float>(weightList);

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

    // Clear Memory
    result.flush();
    return 0;
}
