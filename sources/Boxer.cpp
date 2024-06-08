#include "../headers/Boxer.hpp"
#include <iostream>
Boxer::Boxer() {}

void Boxer::setHealth(int health) { this->health = health; }
int Boxer::getHealth() { return this->health; }

void Boxer::setMaxHealth(int health) 
{ 
    this->maxHealth = health;
    if (this->maxHealth > this->health)
        this->health = this->maxHealth;
}
int Boxer::getMaxHealth() { return this->maxHealth; }

void Boxer::setGuard(int guard) { this->guard = guard; if(this->guard < 0) this->guard = 0; }
int Boxer::getGuard() { return this->guard; }

void Boxer::damage(int damage, bool bypass) 
{ 
    if (bypass) { this->health -= damage; return; }
    
    if (this->guard > 0) 
    {
        this->guard -= damage;
        if (this->guard < 0)
        {
            this->health += guard;
            this->guard = 0;
        }
    }
}

void Boxer::heal(int heal) { this->health += heal; }

void Boxer::addToDeck(Card *card) { this->deck.emplace_back(new Card(*card)); }
void Boxer::removeFromDeck(Card *card) { this->deck.remove(card); }
void Boxer::clearDeck()
{
    for (auto it = this->deck.begin(); it != this->deck.end(); ++it)
    {
        delete *it;
    }
    this->deck.clear();
}

int Boxer::getDeckSize() { return this->deck.size(); }