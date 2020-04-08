//
// Created by litcoderr on 07/04/2020.
//

#include <iostream>
#include <vector>

#include <Tensor.hpp>
#include <WeightMap.hpp>
#include <Optimizer.hpp>
#include <Loss.hpp>

Tensor<float>& model(Tensor<float>& input, WeightMap<float>& weights){
    // Dynamic Graph of Y = W*X+B
    Tensor<float>& output = weights.get("Weight") * input + weights.get("Bias");
    return output;
}

float gt_function(float x){
    return 15 * x + 3;
}

int main(){
    //Initialize Weights
    Variable<float>& weight = *new Variable<float>(15, "Weight");  // Not Distructable
    Variable<float>& bias = *new Variable<float>(10, "Bias");  // Not Distructable
    //Initialize WeightMap
    std::vector<Tensor<float>*> weightList = {&weight, &bias};
    WeightMap<float>& weightMap = *new WeightMap<float>(weightList);
    //Initialize Optimizer
    float learning_rate = 0.001;
    Optimizer<float> optim(&weightMap, learning_rate);
    // Initialize Loss
    L2Loss<float> lossModule;

    // prepare dataset for testing
    std::vector<std::pair<float, float>> dataset;
    for(int x=-10;x<11;x++){
        dataset.push_back(std::make_pair(float(x), gt_function(float(x))));
    }

    int EPOCH = 100;
    for(int epoch=0;epoch<EPOCH;epoch++){
        Tensor<float>* total_loss = new Tensor<float>(0);
        for(std::pair<float, float> data: dataset){
            //Compute Through dynamic graph
            Tensor<float>& x = *new Tensor<float>(data.first);
            Tensor<float>& y = *new Tensor<float>(data.second);

            Tensor<float>& y_ = model(x, weightMap);

            Tensor<float>& loss = lossModule.forward(y_, y); // output, target

            total_loss = &(*total_loss + loss);
        }
        total_loss->backward();

        std::cout << "loss: " << total_loss->data << ", ";
        std::cout << "weight: " << weight.data << ", ";
        std::cout << "bias: " << bias.data << ", ";
        std::cout << "bias_grad: " << bias.grad << std::endl;

        optim.step();
        total_loss->flush();
    }
    return 0;
}
