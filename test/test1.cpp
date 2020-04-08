//
// Created by litcoderr on 07/04/2020.
//

#include <iostream>
#include <vector>

#include <Tensor/Tensor.hpp>
#include <WeightMap.hpp>
#include <Optimizer.hpp>
#include <Loss.hpp>

Tensor<double>& model(Tensor<double>& input, WeightMap<double>& weights){
    // Dynamic Graph of Y = W*X+B
    Tensor<double>& output = (weights.get("Weight") * input) + weights.get("Bias");
    return output;
}

double gt_function(double x){
    return 15 * x + 3;
}

// TODO Implement Tensor Matrix
int main(){
    // Hyper Parameters
    double learning_rate = 0.0001;
    int EPOCH = 1000;

    //Initialize Weights
    Variable<double>& weight = *new Variable<double>(20, "Weight");  // Not Distructable
    Variable<double>& bias = *new Variable<double>(4, "Bias");  // Not Distructable
    //Initialize WeightMap
    std::vector<Tensor<double>*> weightList = {&weight, &bias};
    WeightMap<double>& weightMap = *new WeightMap<double>(weightList);
    //Initialize Optimizer
    Optimizer<double> optim(&weightMap, learning_rate);
    // Initialize Loss
    L2Loss<double> lossModule;

    // prepare dataset for testing
    std::vector<std::pair<double, double>> dataset;
    for(int x=-10;x<11;x++){
        dataset.push_back(std::make_pair(double(x), gt_function(double(x))));
    }

    for(int epoch=0;epoch<EPOCH;epoch++){
        bool first = true;
        Tensor<double>* total_loss = new Tensor<double>();
        for(std::pair<double, double> data: dataset){
            //Compute Through dynamic graph
            Tensor<double>& x = *new Tensor<double>(data.first);
            Tensor<double>& y = *new Tensor<double>(data.second);

            Tensor<double>& y_ = model(x, weightMap);

            Tensor<double>& loss = lossModule.forward(y_, y); // output, target

            total_loss = &(*total_loss + loss);
        }
        total_loss->data /= 20;  // Division by N
        total_loss->backward();

        if(epoch % 10 == 0){
            std::cout << "total_loss: " << total_loss->data << ", ";
            std::cout << "weight: " << weight.data << ", ";
            std::cout << "bias: " << bias.data << std::endl;
        }

        optim.step();
        total_loss->flush();  // Release Memory
    }
    return 0;
}
