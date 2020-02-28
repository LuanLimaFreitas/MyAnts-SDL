#include <vector>
using namespace std;
#include "droplet.h"
#include "parameters.h"
#include "auxiliary_functions.h"

int Droplet::number_of_droplets = 0;

std::vector<std::vector<float>> straight_trail(float noise)
{
    std::vector<float> droplet_center_x_s = {};
    std::vector<float> droplet_center_y_s = {};
    std::vector<float> droplet_origin_times = {};

    int i = 0;
    for( i = 0; i < initial_number_of_droplets; i++)
    {
        float random1 = Uniform();
        float random2 = (Normal()*2 - 1)*noise; // normaly distributed noise between -noise and noise;
        droplet_center_x_s.push_back(x_2*random1 + x_1*(1.-random1));
        droplet_center_y_s.push_back((y_1+y_2)/2 + random2);
        droplet_origin_times.push_back(-Geometric()+1); // Why geometric? Not sure.
    }
    std::vector<std::vector<float>> trail = {droplet_center_x_s,droplet_center_y_s,droplet_origin_times};
    return trail;
}
