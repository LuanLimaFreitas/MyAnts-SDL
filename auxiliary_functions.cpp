#include "auxiliary_functions.h"
#include "parameters.h"

static std::random_device generator;

double Normal()
{
    static std::normal_distribution<float> Normal(0.,1.);
    return Normal(generator);
}

double SmallNormal()
{
    static std::normal_distribution<float> SmallNormal(0.,.05);
    return SmallNormal(generator);
}

double UniformAngle()
{
    static std::uniform_real_distribution<float> UniformAngle(0.,2.*Pi);
    return UniformAngle(generator);
}

double Uniform()
{
    static std::uniform_real_distribution<float> Uniform(0.,1.);
    return Uniform(generator);
}

double UniformInteger()
{
    static std::uniform_int_distribution<int> UniformInteger(0,10);
    return UniformInteger(generator);
}

int Geometric()
{
    static std::geometric_distribution<int> Geometric(0.9);
    return Geometric(generator);
}

float Angle(float X, float Y)
{
    float aux =  atan2(Y,X);
    return aux;
}

float AngleBetween(float x1, float y1, float x2, float y2)
{
    float dot = x1*x2 + y1*y2;
    float det = x1*y2 - y1*x2;
    float aux =  atan2(det,dot);
    return aux;
}

float Heat(float XX, float YY, float elapsed_time, float amount)
{
    float aux = 0.;
    aux = (1. / (4.*Pi* Diffusion * elapsed_time));
    aux *= exp(-(XX*XX + YY*YY) / (4.*Diffusion*elapsed_time));
    aux *= exp(-Evaporation*elapsed_time); // Evaporation .001
    aux *= amount;

    return aux;
}

double Sign(double aa)
{
    if (aa > 0.) return 1.;
    if (aa < 0.) return -1.;
    return 0.;
}

void Periodify(float& x, float& y)
{
    if (x>=x_2 || x<=x_1)
    {
        x = x + Sign(x_2 - x)*(x_2 - x_1);
    }
    if (y>=y_2 || y<=y_1)
    {
        y = y + Sign(y_2 - y)*(y_2 - y_1);
    }
}
