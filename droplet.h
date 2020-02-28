#ifndef DROPLET_H
#define DROPLET_H


////////////////////////////////////////////////////////////
/// Class for a Droplet
////////////////////////////////////////////////////////////
class Droplet
{

public:

    static int number_of_droplets;

    float pos_x,pos_y;
    float origin_time;

    Droplet(float time, float x, float y)
    {
        number_of_droplets++;
        origin_time = time;
        pos_x = x;
        pos_y = y;
    }

    float elapsed_time(float time)
    {
        return time - origin_time;
    }
    int static CountDroplets()
    {
        return number_of_droplets;
    }

};



/// Some pheromone landscape generating facilities.
///
///
std::vector<std::vector<float>> straight_trail(float noise);
/// Generates data for a pheromone trail straight along the x-axis with some Gaussian
/// noise of amplitude 'noise'*2.

#endif // DROPLET_H
