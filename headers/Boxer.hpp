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
    void onUpdate(sf::Vector2f mousePos);

public:
    Boxer();

    void setHealth(int health);
    int getHealth();

    void setMaxHealth(int health);
    int getMaxHealth();

    void setGuard(int guard);
    int getGuard();
    
    void damage(int damage, bool bypass);
    void heal(int heal);

    void addToDeck(Card *card);
    void removeFromDeck(Card *card);
    void clearDeck();
    int getDeckSize();
    
    void burnCard(Card *card) {};

    
    virtual void attack1() {};
    virtual void attack2() {};
    virtual void attack3() {};
    virtual void dead() {};
    virtual void block() {};
};