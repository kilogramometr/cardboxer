#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Healthbar : public Node, sf::RectangleShape
{
private:
    sf::RectangleShape bar;

    sf::Vector2f position;
    sf::Vector2f size;
    float thick;
    bool direction;

    void onDraw(sf::RenderTarget &target);

public:
    Healthbar(bool direct);
    void setHealth(float hp_percent);
};