#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////
/// Class for a Feedforward Neural Network
////////////////////////////////////////////////////////////
///
///
class Network
{

    std::vector<int> sizes;                                /// Stores the sizes of the layers of the Network.
    std::vector<std::vector<std::vector<float>>> weights;  /// Item 'weights[l][i][j]' stores the weight from the i-th neuron ...
                                                           /// ... on the lth layer to the j-th neuron on the l+1-th layer.
    std::vector<std::vector<float>> biases;                /// Item 'biases[l][j]' stores the bias for the j-th neuron on the l+1-th layer ...
                                                           /// ... (since there are no biases for the 0-th layer).
                                                           /// Layers start counting from 0. Beware index hell!

public:
    Network()
    {
    }
    Network( std::vector<int> s, std::vector<std::vector<std::vector<float>>> w, std::vector<std::vector<float>> b)
    {
        sizes = s;
        weights = w;
        biases = b;
    }
    std::vector<float> Feedforward(std::vector<float> input);

    void print_parameters()
    {
        cout << "Ola" << endl;
        int i;
        cout << sizes.size() << endl;
        for(i=0;i<sizes.size();i++)
            cout << sizes[i] << endl;
    };
};
///
///
///
///



#endif // NETWORK_H
