#include "../headers/Player.hpp"

Player::Player()
{
    this->healthbar = new Healthbar(0);
    this->appendChild(this->healthbar);

    //Setting health to 80%
    this->healthbar->setHealth(80);

    this->shield = new Shield();
    this->appendChild(this->shield);

    this->initSprite();
}

void Player::initSprite()
{
    this->idleTexture.loadFromFile("../res/textures/Fighter/Idle.png");
    this->attack1Texture.loadFromFile("../res/textures/Fighter/Attack_1.png");
    this->attack2Texture.loadFromFile("../res/textures/Fighter/Attack_2.png");
    this->attack2Texture.loadFromFile("../res/textures/Fighter/Attack_3.png");
    this->deadTexture.loadFromFile("../res/textures/Fighter/Dead.png");

    this->sprite.setTexture(this->idleTexture);
    this->sprite.setTextureRect(sf::IntRect(46, 47, 30, 81));
    this->sprite.setScale(sf::Vector2f(1.5, 1.5));
    this->sprite.setPosition(sf::Vector2f(200, 320));

    this->setIdle();
}

void Player::onDraw(sf::RenderTarget &target, sf::Transform& transform)
{
    target.draw(this->sprite, transform);
}

void Player::animate()
{
    if(this->animationTimer > 5)
    {
        if(this->frame < this->maxFrame)
        {
            this->frame += 1;
            this->animationTimer = 0;
            this->setFrame();
        }
        else
        {
            this->setIdle();
            this->setFrame();
        }
    }
    else
    {
        this->animationTimer += 1;
    }

    
}

void Player::setFrame()
{
    if(this->animationType == 0)
    {
        switch(this->frame)
        {
            case 1:
                this->sprite.setTextureRect(sf::IntRect(46, 47, 35, 81));
                std::cout<<"Idle frame 1"<<std::endl;
                break;
            case 2:
                this->sprite.setTextureRect(sf::IntRect(174, 47, 35, 81));
                std::cout<<"Idle frame 2"<<std::endl;
                break;
            case 3:
                this->sprite.setTextureRect(sf::IntRect(301, 47, 35, 81));
                std::cout<<"Idle frame 3"<<std::endl;
                break;
            case 4:
                this->sprite.setTextureRect(sf::IntRect(428, 47, 35, 81));
                std::cout<<"Idle frame 4"<<std::endl;
                break;
            case 5:
                this->sprite.setTextureRect(sf::IntRect(557, 47, 35, 81));
                std::cout<<"Idle frame 5"<<std::endl;
                break;
            case 6:
                this->sprite.setTextureRect(sf::IntRect(686, 47, 35, 81));
                std::cout<<"Idle frame 6"<<std::endl;
                break;
        }
    }
}

void Player::onUpdate()
{
    this->animate();
}

void Player::setIdle()
{
    this->sprite.setTexture(this->idleTexture);
    this->animationType=0;
    this->frame=1;
    this->maxFrame=6;
    this->animationTimer=0;
}

void Player::setAttack1()
{
    this->sprite.setTexture(this->attack1Texture);
    this->animationType = 1;
    this->frame = 1;
    this->maxFrame = 4;
    this->animationTimer = 0;
}