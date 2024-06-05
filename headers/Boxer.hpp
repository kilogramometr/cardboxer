#pragma once
#include "Card.hpp"
#include "Node.hpp"
#include "Healtbar.hpp"
#include <list>

class Boxer : public Node
{
protected:
    Healthbar *healthbar;
    int health;
    int maxHealth;
    int guard;
    std::list<Card *> deck;

    void updateHealthbar();

public:
    Boxer();

    void setHealth(int health);
    int getHealth(int health);

    void setMaxHealth(int health);
    int getMaxHealth(int health);

    void setGuard(int guard);
    int getGuard(int guard);
    
    void damage(int damage);
    void heal(int heal);

    void addToDeck(Card *card);
    void removeFromDeck(Card *card);
};