#include "../headers/utils.hpp"
#include <random>

int randomUniform(int min, int max)
/* return single integer selected randomly from <min, max> distributed uniformly */
{
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> uni_distribution(min, max);
    return uni_distribution(engine);
}