/*
*   this is a mcmc sampler(Metropolis-Hastings) example
*   author : Kaijiang.Chen
*/

#include <iostream>
#include <cmath>
using namespace std;
#include <ctime>
#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/variate_generator.hpp>

double StdNormal(double z)
{
    return exp(-z * z / 2.0) * sqrt(2 * 3.1416);
}

uint32_t seed = time(0);
double Uniform(double min, double max)
{
    boost::mt19937 randomNumbergenerator(seed++);
    boost::random::uniform_real_distribution< > uniformDistribution(min, max);
    boost::variate_generator< boost::mt19937&, boost::random::uniform_real_distribution < > >
        generateRandomNumbers( randomNumbergenerator, uniformDistribution );
    return  generateRandomNumbers(); 
};


int main(int c, char** v)
{
    double floor = -1;
    double ceil = 1;
    vector<double> states;
    uint32_t states_num = 10000;
    // we take uniform distribution as the Q
    for(uint32_t i = 0; i < states_num; i++)
    {
        states.push_back(Uniform(floor, ceil));
    }

    // simulate standard normal distribution:
    double x = 0;
    for(uint32_t i = 0; i < states_num; i++)
    {
        double candidate = x + states[i];
        double accept_prob = StdNormal(candidate)/StdNormal(x);
        accept_prob = 1 > accept_prob ? accept_prob : 1;
        double u = Uniform(0, 1);
        if(u < accept_prob)
            x = candidate;
        cout << x << endl;
    }
    return 0;
}
