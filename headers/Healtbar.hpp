#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Healthbar : public Node, sf::RectangleShape
{
private:
    bool direction;

public:
    Healthbar(sf::Vector2f position, bool direct);
    void setHealth(float hp);
};