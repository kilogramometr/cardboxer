#pragma once
#include "Boxer.hpp"

class Enemy : public Boxer, public sf::Sprite
{
private:
    std::list<float> probabilities; 
    std::list<Card *>::iterator lastPlayed; // last played card
    sf::Texture *texture;
    int frames;
    int frameWidth;
    int frameHeight;
    sf::Vector2f framePos;
    sf::Text name;

public:
    Enemy(Json::Value enemy, std::list<Card *>& library);

    std::list<Card *>::iterator chooseCard();
    void playCard();
    void nextFrame();
    void prevFrame();
    void setFrame();
    
};