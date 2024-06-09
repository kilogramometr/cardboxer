#include "../headers/utils.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <time.h>

int randomUniform(int min, int max)
/* return single integer selected randomly from <min, max> distributed uniformly */
{
    // std::cerr<<min<<" "<<max<<"\n";
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> uni_distribution(min, max);
    return uni_distribution(engine);
}

const std::string currentDateTime() { // shamelessly stolen from stackoverflow.com credit to users TrungTN and Rashad
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void log(std::string log)
{
    std::ofstream file("log.txt", std::ios::app);
    std::string now = currentDateTime();
    std::string msg = now + " " + log;

    if (file.is_open())
    {
        file << msg;
    }
    file.close();
}