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

    int charakter;

    int frame;
    int maxFrame;
    int animationTimer;
    int animationType;

    sf::Texture sam_idleTexture;
    sf::Texture sam_attack1Texture;
    sf::Texture sam_attack2Texture;
    sf::Texture sam_attack3Texture;
    sf::Texture sam_deadTexture;

    sf::Texture shi_idleTexture;
    sf::Texture shi_attack1Texture;
    sf::Texture shi_attack2Texture;
    sf::Texture shi_attack3Texture;
    sf::Texture shi_deadTexture;

    void construct(int charakter);
    void loadSprites();

    void animate();
    void setAnimationFrame();
    void onUpdate();
    void onDraw(sf::RenderTarget &target, sf::Transform& transform);

    void setIdle();
    void setAttack1();
    void setAttack2();
    void setAttack3();
    void setDead();

public:
    Enemy(Json::Value enemy, std::list<Card *>& library, int charakter=0);
    Enemy(int charakter=0);

    std::list<Card *>::iterator chooseCard();
    void playCard();
    void nextFrame();
    void prevFrame();
    void setFrame();

    //Animations
    void attack1();
    void attack2();
    void attack3();
    void dead();
};