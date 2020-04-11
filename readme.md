# AutoGrad
> Auto Gradient Computation Framework (Pytorch Mock Version)

## Usage
Example code can be viewed here.

1. Tensor node Test: [Code](https://github.com/litcoderr/AutoGradCpp/blob/master/test/test1.cpp)
2. Matrix Test: [Code](https://github.com/litcoderr/AutoGradCpp/blob/master/test/test2.cpp)

### Tensor
- Tensor node.
- Destructible node when flushing memory recursively by default.

#### Initialize
```c++
#include <Tensor/Tensor.hpp>

Tensor<double>& my_tensor1 = *new Tensor<double>(); // default value 0
Tensor<double>& my_tensor2 = *new Tensor<double>(3.2); // value only with default name as ""
Tensor<double>& my_tensor3 = *new Tensor<double>(3.2, "Data"); // value only and custom name
```

#### Generating Dynamic Graph
```c++
// ADD, SUBTRACT, MULTIPLY operations will automatically generate Dynamic Graph
Tensor<double>& result = my_tensor1 + my_tensor2 - my_tensor3 * my_tensor4
```

#### Back Propagation
```c++
result.backward(); // EASY. check each tensor's .grad element for gradient value
```

#### Flush Memory
```c++
Tensor<double>& head_node_of_graph;

head_node_of_graph.flush(); // will flush all child node memories
```

### Variable
- Inherits Tensor
- Not Destructible node when flushing memory recursively by default. (Used for weights)

#### Initialize
```c++
#include <Tensor/Tensor.hpp>

Variable<double>& my_tensor1 = *new Variable<double>(); // default value 0
Variable<double>& my_tensor2 = *new Variable<double>(3.2); // value only with default name as ""
Variable<double>& my_tensor3 = *new Variable<double>(3.2, "Weights"); // value only with default name as ""
```

### WeightMap
- Contains weight tensors in a map
- Tensors can be retrieved by std::string key

#### Initialize
```c++
#include <WeightMap.hpp>
#include <Tensor/Tensor.hpp>

// Initialize weights
Variable<double>& weight1 = *new Variable<double>(1.1, "W1"); 
Variable<double>& weight2 = *new Variable<double>(1.2, "W2"); 
Variable<double>& weight3 = *new Variable<double>(1.3, "W3");

// Initialize Weight Map
std::vector<Tensor<double>*> weight_list = {weight1, weight2, weight3};  // first make vector with type Tensor<T>*
WeightMap<double>& weightMap = *new WeightMap<double>(weight_list);  // Initialize by passing in weight list
```

#### Get Tensor
```c++
Tensor<float>& weight_i_want = weightMap.get("Weight");  // use key std::string to retrieve reference
```

### Optimizer
- Takes in WeightMap Pointer and Learning Rate

#### Initialize
```c++
#include <Optimizer.hpp>

#include <WeightMap.hpp>
#include <Tensor/Tensor.hpp>
WeightMap<double>& weightMap = *new WeightMap<double>(weight_list);  // Initialize by passing in weight list
double learning_rate = 0.0001;

Optimizer<double> optim(&weightMap, learning_rate);
```

#### Update Weights
```c++
optim.step();  // EASY.
```

### Loss
- Loss Instance for Loss Calculation

#### Initialize
```c++
#include <Loss.hpp>

Loss<double> lossModule;
```

#### Forward Propagate Loss
```c++
Tensor<double>& model_output;
Tensor<double>& target;

Tensor<double>& loss = lossModule.forward(model_output, target);  // pass in model_output and target to forward method
```