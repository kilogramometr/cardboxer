#include "../headers/Healtbar.hpp"

Healthbar::Healthbar(sf::Vector2f position, bool direction)
{
    this->setSize(sf::Vector2f(50, 400));
    this->setFillColor(sf::Color::Green);
    this->setPosition(position);
    this->direction = direction;
}

void Healthbar::setHealth(float hp)
{
    if(this->direction == 0)
    {
        this->setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y + (this->getGlobalBounds().height / (hp/100))));
    }
    else
    {
        this->setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - (this->getGlobalBounds().height / (hp/100))));
    }
}