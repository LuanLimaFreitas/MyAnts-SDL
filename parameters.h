#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <vector>
#include <string>
using namespace std;

extern float delta_t;

extern int number_of_ants;
extern int initial_number_of_droplets;

extern int number_of_iterations;

extern float const drop_every_iter;

extern float const droplet_too_old;

extern float sensing_area_radius;

extern float const Pi;

extern float sensing_area_half_angle;

extern float const Diffusion;
extern float const Evaporation;
extern float const Amount;

extern float const ignore_droplet_if_this_far;
extern float const ignore_droplet_if_this_far2;

extern float const x_1;
extern float const x_2;
extern float const y_1;
extern float const y_2;
extern float Lx;
extern float Ly;
extern std::vector<float> N;
extern std::vector<float> S;
extern std::vector<float> W;
extern std::vector<float> E;
extern std::vector<float> NW;
extern std::vector<float> NE;
extern std::vector<float> SW;
extern std::vector<float> SE;
extern std::vector<std::vector<float>> neighbor_squares;

extern float zoom_multiplier;

extern int const seed1;

extern float const tau;

extern float const threshold;

extern std::string const BoundaryMethod;

#endif // PARAMETERS_H
