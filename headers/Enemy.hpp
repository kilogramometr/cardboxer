#pragma once
#include "Boxer.hpp"
#include "Shield.hpp"

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

    Shield *shield;
    Sprite sprite;
    int charakter;
    sf::Texture sam_idleTexture;
    sf::Texture sam_attack1Texture;
    sf::Texture sam_attack2Texture;
    sf::Texture sam_attack3Texture;
    sf::Texture sam_deadTexture;

    sf::Texture shi_idleTexture;
    sf::Texture shi_attack1Texture;
    sf::Texture shi_attack2Texture;
    sf::Texture shi_attack3Texture;
    sf::Texture shi_dead;

    void loadSprites();

    void onDraw(sf::RenderTarget &target, sf::Transform& transform);
    std::list<Card *>::iterator chooseCard();
public:
    Enemy(Json::Value enemy, std::list<Card *>& library);
    Enemy();

    Card* playCard();
    void nextFrame();
    void prevFrame();
    void setFrame();
    
};