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
    bool *animationEnd;

    sf::Texture sam_idleTexture;
    sf::Texture sam_attack1Texture;
    sf::Texture sam_attack2Texture;
    sf::Texture sam_attack3Texture;
    sf::Texture sam_deadTexture;
    sf::Texture sam_blockTexture;

    sf::Texture shi_idleTexture;
    sf::Texture shi_attack1Texture;
    sf::Texture shi_attack2Texture;
    sf::Texture shi_attack3Texture;
    sf::Texture shi_deadTexture;
    sf::Texture shi_blockTexture;

    sf::Texture vam_idleTexture;
    sf::Texture vam_attack1Texture;
    sf::Texture vam_attack2Texture;
    sf::Texture vam_attack3Texture;
    sf::Texture vam_deadTexture;
    sf::Texture vam_blockTexture;

    void construct(int charakter);
    void loadSprites();

    void animate();
    void setAnimationFrame();
    void onDraw(sf::RenderTarget &target, sf::Transform& transform);
    std::list<Card *>::iterator chooseCard();
    void onUpdate(sf::Vector2f mousePos);

    void setIdle();
    void setAttack1();
    void setAttack2();
    void setAttack3();
    void setDead();
    void setBlock();

public:
    Enemy(Json::Value enemy, std::list<Card *>& library, int charakter=0);
    Enemy(int charakter=0);
    Enemy(Enemy *copy);

    Card* playCard();
    void nextFrame();
    void prevFrame();
    void setFrame();

    //Animations
    void attack1();
    void attack2();
    void attack3();
    void dead();
    void dead(bool *animationEnd);
    void block();
    std::string getName();
};