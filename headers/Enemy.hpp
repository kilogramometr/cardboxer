#pragma once
#include "Boxer.hpp"

class Enemy : public Boxer
{
private:
    std::list<float> probabilities; 
    std::list<Card *>::iterator lastPlayed; // last played card

public:
    Enemy(Json::Value enemy);

    std::list<Card *>::iterator chooseCard();
    void playCard();
    
};