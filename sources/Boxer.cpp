#include "../headers/Boxer.hpp"
#include <iostream>
Boxer::Boxer()
{
    
}

void Boxer::setHealth(int health) { this->health = health; }
int Boxer::getHealth(int health) { return this->health; }

void Boxer::setMaxHealth(int health) { this->maxHealth = health; }
int Boxer::getMaxHealth(int health) { return this->maxHealth; }

void Boxer::setGuard(int guard) { this->guard = guard; }
int Boxer::getGuard(int guard) { return this->guard; }

void Boxer::damage(int damage) { this->health -= damage; } 
void Boxer::heal(int heal) { this->health += heal; }

void Boxer::addToDeck(Card *card) { this->deck.emplace_back(new Card(*card)); }
void Boxer::removeFromDeck(Card *card) { this->deck.remove(card); }
