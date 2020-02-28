#include <cmath>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
using namespace std;

#include "auxiliary_functions.h"
#include "parameters.h"
#include "globals.h"

#include "network.h"
#include "droplet.h"
#include "ant.h"
#include "window.h"


int cycle_count;
int last_drop_iter;
float score;

void initialize_ants(Network Net);
/// Initialize the ants at random positions.
void initialize_pheromone_lanscape();
/// Initialize the pheromone landscape -- currently initializing a straight
/// trail of pheromone droplets.
Network Std_Net();
/// Spits a manually defined Network.
///
void Cycle();
/// One (1) cycle of ant updating, pheromone droping and pheromone
/// erasing.

int main(int argc, char* argv[])
{
    initialize_ants(Std_Net());
    initialize_pheromone_lanscape();
    cycle_count = 0;
    score = 0;

    Window window("M Y    A N T S   - -   A   V I S U A L   I M P L E M E N T A T I O N", Lx, Ly);
    window.clear();

    while(!window.isClosed() && cycle_count < number_of_iterations)
    {
        window.pollEvents();
        Cycle();
        window.display(cycle_count);
    }

    cout << "Scored <" << score << "> over <" << cycle_count << "> cycles." << endl;

    return 0;

}


void initialize_ants(Network Net)
{
    std::size_t i;

    for ( i = 0; i<number_of_ants; i++)
    {
        all_ants.push_back(new Ant());
        all_ants[i]->load_at_random(Net);
    }
}

void initialize_pheromone_lanscape()
{
    std::size_t i;

    last_drop_iter = -999;  // '-999' is just a small enough number.
    std::vector<std::vector<float>> trail = straight_trail(0.);
    for (  i = 0; i<initial_number_of_droplets; i++)
    {
        float droplet_center_x = trail[0][i];
        float droplet_center_y = trail[1][i];
        float droplet_origin_time = trail[2][i];
        if( droplet_origin_time > last_drop_iter)  // We wish to record the nearest (greatest) 'droplet_origin_time'.
            last_drop_iter = droplet_origin_time;
        all_droplets.push_back(Droplet(droplet_origin_time,droplet_center_x,droplet_center_y));
    }

    Droplet::number_of_droplets = initial_number_of_droplets;
}

Network Std_Net()
{
    std::vector<int> s = {2,2};
    std::vector<std::vector<std::vector<float>>> w = { {{1,0},{0,0.5}} };
    std::vector<std::vector<float>> b = { {0,0} };
    Network _Net(s,w,b);
    return _Net;
}

void Cycle()
{
    std::size_t j;
    /// Step A: Check if it's time to leave some droplets
    /// - Probably a good time to erase some droplets too!
    ///
    if( cycle_count - last_drop_iter >= drop_every_iter)
    {
        last_drop_iter = cycle_count;
        for( j=0 ; j < all_ants.size(); j++ )
            all_droplets.push_back(Droplet(cycle_count,all_ants[j]->pos_x,all_ants[j]->pos_y));
        /// Now checking for outdated droplets.
        for( j=0; j < all_droplets.size(); j++ ) // Improve this!
        {
            if (exp(-Evaporation * all_droplets[j].elapsed_time(cycle_count)) * Amount <= 10.)
            {
                all_droplets.erase(all_droplets.begin()+j);
                Droplet::number_of_droplets--;
            }
        }
    }
    else
    {    /// Step B: Update our little anties and record the pheromone they feel. The ants
         /// will either drop pheromone or walk. This is meant to avoid undetermined results
         /// in the heat equation when 'elapsed time' = 0. Still, it appears to be a reasonable
         /// and natural behavior.
        for( j=0; j<all_ants.size(); j++ )
        {
            float some_points = all_ants[j]->update(cycle_count,all_droplets); // Sounds easy, eh?
            score += some_points;
        }
    }
    cycle_count++;
}
