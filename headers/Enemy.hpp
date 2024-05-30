#pragma once
#include "Node.hpp"
#include "Healtbar.hpp"

class Enemy : public Node
{
private:
    Healthbar *healthbar;

public:
    Enemy();
};