#include "../headers/Healtbar.hpp"

Healthbar::Healthbar(bool direction)
{
    // You can adjust that, everythink will still work
    this->size = {50, 400};
    this->thick = 5;

    //Frame
    if(direction == 0) this->position = {0, 600 - size.y};
    else this->position = {800 - size.x, 0};

    this->setPosition(sf::Vector2f(position.x+this->thick, position.y+this->thick));
    this->setSize(sf::Vector2f(size.x - 2*this->thick, size.y - 2*this->thick));
    this->setOutlineThickness(this->thick);

    this->setFillColor(sf::Color::Transparent);
    this->setOutlineColor(sf::Color::White);
    
    //Bar
    this->bar.setPosition(sf::Vector2f(position.x+this->thick, position.y+this->thick));
    this->bar.setSize(sf::Vector2f(size.x - 2*this->thick, size.y - 2*this->thick));
    this->bar.setFillColor(sf::Color::Green);

    this->direction = direction;
}

void Healthbar::setHealth(float hp_percent)
{
    if(this->direction == 0) this->bar.setPosition(this->position.x+this->thick, this->position.y+this->thick + this->bar.getSize().y*(1-hp_percent/100));
    else this->bar.setPosition(this->position.x+this->thick, this->position.y+this->thick - this->bar.getSize().y*(1-hp_percent/100));
}

void Healthbar::onDraw(sf::RenderTarget &target)
{
    target.draw(this->bar);
    target.draw(*this);
}