#include "../headers/Enemy.hpp"

Enemy::Enemy()
{
    this->healthbar = new Healthbar(1);
    this->appendChild(this->healthbar);

    //Setting health to 100%
    this->healthbar->setHealth(30);
}