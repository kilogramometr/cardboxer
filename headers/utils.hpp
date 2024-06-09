#pragma once
#include <string>

int randomUniform(int min, int max);

void log(std::string log);

enum Animation 
{
    DEATH = 0,
    idle = 1,
    attack1 = 2,
    attack2 = 3,
    attack3 = 4,
    block = 5
};