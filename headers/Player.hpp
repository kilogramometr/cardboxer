#pragma once
#include "Node.hpp"
#include "Healtbar.hpp"

class Player : public Node
{
private:
Healthbar *healthbar;

public:
    Player();
};