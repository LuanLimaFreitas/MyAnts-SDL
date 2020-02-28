#include "network.h"

float sigmoid(float x)   /// Will be used as activation function.
{
    return 1/(1+std::exp(-x));
}

float sigmoid_(float x)   /// For test purposes.
{
    return x;
}

std::vector<float> Network::Feedforward(std::vector<float> input)
{

    std::vector<float> activations = input;              /// 'activations' will be updated as we Feedforward.
    int num_layers = sizes.size();
    int layer;                                           /// 'layer' is to be interpreted here as (in general) the layer we're ...
                                                         /// ... advancing from, i.e., from 'layer' to 'layer'+1.
    for( layer=0; layer<num_layers-1; layer++)
    {
        std::vector<float> sums(sizes[layer+1], 0.);     /// Blank vector to receive the weighted signals.
        int neuron_from,neuron_to;
        for( neuron_from=0; neuron_from<sizes[layer]; neuron_from++)         /// Feedforwarding for each pair of neurons...
            for( neuron_to=0; neuron_to<sizes[layer+1]; neuron_to++)
                sums[neuron_to] += activations[neuron_from]*weights[layer][neuron_from][neuron_to];

        for( neuron_to=0; neuron_to<sizes[layer+1]; neuron_to++)             /// Add biases and traverse the activation function.
        {
            sums[neuron_to] = sums[neuron_to] - biases[layer][neuron_to];    /// Beware the particular meaning of 'layer' in this sentence.
            activations[neuron_to] = sigmoid(sums[neuron_to]);
        }
    }

    return activations;
}
