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
    //Initialize Weights
    Variable<float>& weight = *new Variable<float>(2, "Weight");  // Not Distructable
    Variable<float>& bias = *new Variable<float>(3, "Bias");  // Not Distructable
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
