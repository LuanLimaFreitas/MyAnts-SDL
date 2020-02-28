#ifndef ANT_H
#define ANT_H

#include<vector>
#include<iostream>
using namespace std;
#include "droplet.h"
#include "network.h"

////////////////////////////////////////////////////////////
/// Class for an Ant
////////////////////////////////////////////////////////////
class Ant
{
public:

    Ant()
    {
    }

    float pos_x,pos_y;
    float pos_old_x,pos_old_y;
    float antenna_L_x,antenna_L_y;
    float antenna_R_x,antenna_R_y;
    float sting_pos_x,sting_pos_y;
    float vel_x,vel_y;
    float vel_old_x, vel_old_y;
    float force_x,force_y;
    Network Net;

    bool load_at_random(Network _Net);
    bool load_at(float x, float y, Network _Net);
    float update(float time, std::vector<Droplet>& pheromone);
    float Compute_Force_with_Net(float time, std::vector<Droplet>& pheromone);
    float FeltPheromone(float time, float x, float y, std::vector<Droplet>& pheromone);
    void Boundarify();
    void ShowPosition()
    {
        std::cout << "x = "<< pos_x << ", y = " << pos_y << "\n";
    }

//private:

};

#endif // ANT_H
