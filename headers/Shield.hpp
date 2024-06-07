#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Node.hpp"

class Shield : public Node, sf::Sprite
{
private:
    int points;

    sf::Texture texture;
    sf::Text text;
    sf::Font font;

    void setSprite();
    void setText();

    void onDraw(sf::RenderTarget &target, sf::Transform& transform);
public:
    Shield();
    void setPoints(int points);
};