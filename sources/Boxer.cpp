#include "../headers/Boxer.hpp"

Boxer::Boxer()
{
    this->healthbar = new Healthbar(0);
    this->appendChild(this->healthbar);

    //Setting health to 80%
    this->healthbar->setHealth(80);
    
}