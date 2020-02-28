#include<vector>
#include "ant.h"
#include "auxiliary_functions.h"
#include "parameters.h"
#include "network.h"
#include <iostream>
using namespace std;

bool Ant::load_at_random(Network _Net)
{
    Net = _Net;

    float x = x_2*Uniform() + x_1*(1.-Uniform());
    float y = y_2*Uniform() + y_1*(1.-Uniform());
    pos_x = x;
    pos_y = y;
    pos_old_x = pos_x;
    pos_old_y = pos_y;
    float iniangle = UniformAngle();
    vel_x = cos(iniangle);
    vel_y = sin(iniangle);
    float norm = sqrt(vel_x*vel_x + vel_y*vel_y)/10.;
    vel_x /= norm;
    vel_y /= norm;
    vel_old_x = vel_x;
    vel_old_y = vel_y;

    float xl = pos_x + sensing_area_radius * cos(Angle(vel_x,vel_y)-sensing_area_half_angle);
    float yl = pos_y + sensing_area_radius * sin(Angle(vel_x,vel_y)-sensing_area_half_angle);
    float xr = pos_x + sensing_area_radius * cos(Angle(vel_x,vel_y)+sensing_area_half_angle);
    float yr = pos_y + sensing_area_radius * sin(Angle(vel_x,vel_y)+sensing_area_half_angle);
    antenna_L_x = xl;
    antenna_L_y = yl;
    antenna_R_x = xr;
    antenna_R_y = yr;

    return true;
}
bool Ant::load_at(float x, float y, Network _Net)
{
    Net = _Net;

    pos_x = x;
    pos_y = y;

    pos_old_x = pos_x;
    pos_old_y = pos_y;
    float iniangle = UniformAngle();
    vel_x = cos(iniangle);
    vel_y = sin(iniangle);
    float norm = sqrt(vel_x*vel_x + vel_y*vel_y)/10;
    vel_x /= norm;
    vel_y /= norm;
    vel_old_x = vel_x;
    vel_old_y = vel_y;

    float xl = pos_x + sensing_area_radius * cos(Angle(vel_x,vel_y)-sensing_area_half_angle);
    float yl = pos_y + sensing_area_radius * sin(Angle(vel_x,vel_y)-sensing_area_half_angle);
    float xr = pos_x + sensing_area_radius * cos(Angle(vel_x,vel_y)+sensing_area_half_angle);
    float yr = pos_y + sensing_area_radius * sin(Angle(vel_x,vel_y)+sensing_area_half_angle);
    antenna_L_x = xl;
    antenna_L_y = yl;
    antenna_R_x = xr;
    antenna_R_y = yr;

    return true;
}
float Ant::update(float time, std::vector<Droplet> &pheromone)
{
    float felt_pheromone = Compute_Force_with_Net(time, pheromone);
    pos_x = pos_old_x + delta_t * vel_old_x;
    pos_y = pos_old_y + delta_t * vel_old_y;
    vel_x = vel_old_x + delta_t * (1./tau) * (-vel_old_x + force_x);
    vel_y = vel_old_y + delta_t * (1./tau) * (-vel_old_y + force_y);
    float norm = sqrt(vel_x*vel_x + vel_y*vel_y)/10.;
    //vel_x /= norm;
    //vel_y /= norm;
    Boundarify();
    pos_old_x = pos_x;
    pos_old_y = pos_y;
    vel_old_x = vel_x;
    vel_old_y = vel_y;
    antenna_L_x = pos_x + sensing_area_radius * cos(Angle(vel_x,vel_y)-sensing_area_half_angle);
    antenna_L_y = pos_y + sensing_area_radius * sin(Angle(vel_x,vel_y)-sensing_area_half_angle);
    antenna_R_x = pos_x + sensing_area_radius * cos(Angle(vel_x,vel_y)+sensing_area_half_angle);
    antenna_R_y = pos_y + sensing_area_radius * sin(Angle(vel_x,vel_y)+sensing_area_half_angle);

    return felt_pheromone;
}
float Ant::Compute_Force_with_Net(float time, std::vector<Droplet>& pheromone)
{
    float felt_pheromone;
    float ax = pos_x;
    float ay = pos_y;
    float alx = antenna_L_x;
    float aly = antenna_L_y;
    float arx = antenna_R_x;
    float ary = antenna_R_y;
    float fpl = FeltPheromone(time, antenna_L_x,antenna_L_y,pheromone);
    float fpr = FeltPheromone(time, antenna_R_x,antenna_R_y,pheromone);
    std::vector<float> coeficients = Net.Feedforward({fpl,fpr});
    float c_l = coeficients[0];
    float c_r = coeficients[1];
    float denom = c_l + c_r;
    float numerx = (alx - ax)*c_l + (arx - ax)*c_r;
    float numery = (aly - ay)*c_l + (ary - ay)*c_r;
    force_x = numerx/denom;
    force_y = numery/denom;

    felt_pheromone = fpl + fpr;
    return felt_pheromone;

}
float Ant::FeltPheromone(float time, float x, float y, std::vector<Droplet>& pheromone)
{
    float result = 0.;
    float dx, dy;
    float elapsed_time;
    // neighbor_squares is defined in parameters.cpp:
    // std::vector<std::vector<float>> neighbor_squares = {N,S,W,E,NW,NE,SW,SE};

    int NN = Droplet::CountDroplets();
    for (int i=0; i<NN; ++i)
    {
        // Current droplet
        Droplet& dd = pheromone[i];
        dx = x-dd.pos_x;
        dy = y-dd.pos_y;
        elapsed_time = time - dd.origin_time;
        if (BoundaryMethod=="periodic")
        {
            float dist = (dx*dx + dy*dy);
            if (dist*0 <= ignore_droplet_if_this_far2)    // Careful... this does not measure across periodic Boundary!
            {
                float h = Heat(dx,dy,elapsed_time,Amount);
                result += h;
                for (std::size_t dir=0; dir<neighbor_squares.size(); dir++)
                {
                    h = Heat(dx+neighbor_squares[dir][0],dy+neighbor_squares[dir][1],elapsed_time,Amount);
                    result += h;
                }

            }
        }
        if (BoundaryMethod=="reflective")
        {
            float dist = (dx*dx + dy*dy);
            if (dist*0 <= ignore_droplet_if_this_far2)    // Careful... this does not measure across periodic Bdry!
            {
                result += Heat(dx,dy,elapsed_time,Amount);
            }
        }

    }

    return std::max(threshold,result);
}
void Ant::Boundarify()
{
    if (BoundaryMethod == "reflective")
    {
        float newposx = std::max(x_1,std::min(x_2,pos_x));
        if (newposx == x_1 || newposx == x_2)
        {
            vel_x = -vel_x;
        }
        float newposy = std::max(y_1,std::min(y_2,pos_y));
        if (newposy == x_1 || newposy == x_2)
        {
            vel_y = -vel_y;
        }
    }
    if (BoundaryMethod == "periodic")
    {
        Periodify(pos_x,pos_y);
        Periodify(antenna_L_x,antenna_L_y);
        Periodify(antenna_R_x,antenna_R_y);
    }

}
