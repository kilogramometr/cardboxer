#include "../headers/Player.hpp"

Player::Player()
{
    this->healthbar = new Healthbar(0);
    this->appendChild(this->healthbar);

    //Setting health to 100%
    this->healthbar->setHealth(80);
    
}