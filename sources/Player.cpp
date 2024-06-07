#include "../headers/Player.hpp"

Player::Player()
{
    this->healthbar = new Healthbar(0);
    this->appendChild(this->healthbar);

    //Setting health to 80%
    this->healthbar->setHealth(80);
}