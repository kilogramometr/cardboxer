#include "../headers/Player.hpp"

Player::Player() : Boxer()
{
    this->healthbar = new Healthbar(0);
    this->appendChild(this->healthbar);
    this->healthbar->setHealth(100);

    this->shield = new Shield(0);
    this->appendChild(this->shield);

    this->initSprite();
}

void Player::initSprite()
{
    this->idleTexture.loadFromFile("../res/textures/Fighter/Idle.png");
    this->attack1Texture.loadFromFile("../res/textures/Fighter/Attack_1.png");
    this->attack2Texture.loadFromFile("../res/textures/Fighter/Attack_2.png");
    this->attack3Texture.loadFromFile("../res/textures/Fighter/Attack_3.png");
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

void Player::onUpdate()
{
    this->healthbar->setHealth(this->health);
    this->shield->setPoints(this->guard);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        this->attack1();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        this->attack2();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        this->attack3();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        this->dead();

    this->animate();
}

void Player::animate()
{
    if(this->animationTimer > 5)
    {
        if(this->frame < this->maxFrame)
        {
            this->frame += 1;
            this->animationTimer = 0;
        }
        else
        {
            this->setIdle();
        }
    }
    else
    {
        this->animationTimer += 1;
    }
    this->setFrame();
}

void Player::setFrame()
{
    if(this->animationType == 0)
    {
        switch(this->frame)
        {
            case 1:
                this->sprite.setTextureRect(sf::IntRect(46, 47, 35, 81));
                //std::cout<<"Idle frame 1"<<std::endl;
                break;
            case 2:
                this->sprite.setTextureRect(sf::IntRect(174, 47, 35, 81));
                //std::cout<<"Idle frame 2"<<std::endl;
                break;
            case 3:
                this->sprite.setTextureRect(sf::IntRect(301, 47, 35, 81));
                //std::cout<<"Idle frame 3"<<std::endl;
                break;
            case 4:
                this->sprite.setTextureRect(sf::IntRect(428, 47, 35, 81));
                //std::cout<<"Idle frame 4"<<std::endl;
                break;
            case 5:
                this->sprite.setTextureRect(sf::IntRect(557, 47, 35, 81));
                //std::cout<<"Idle frame 5"<<std::endl;
                break;
            case 6:
                this->sprite.setTextureRect(sf::IntRect(686, 47, 35, 81));
                //std::cout<<"Idle frame 6"<<std::endl;
                break;
        }
    }
    else if(this->animationType == 1)
    {
        switch(this->frame)
        {
            case 1:
                this->sprite.setTextureRect(sf::IntRect(38, 47, 60, 81));
                //std::cout<<"Attack1 frame 1"<<std::endl;
                break;
            case 2:
                this->sprite.setTextureRect(sf::IntRect(166, 47, 60, 81));
                //std::cout<<"Attack1 frame 2"<<std::endl;
                break;
            case 3:
                this->sprite.setTextureRect(sf::IntRect(295, 47, 60, 81));
                //std::cout<<"Attack1 frame 3"<<std::endl;
                break;
            case 4:
                this->sprite.setTextureRect(sf::IntRect(423, 47, 60, 81));
                //std::cout<<"Attack1 frame 4"<<std::endl;
                break;
        }
    }
    else if(this->animationType == 2)
    {
        switch(this->frame)
        {
            case 1:
                this->sprite.setTextureRect(sf::IntRect(36, 47, 60, 81));
                //std::cout<<"Attack2 frame 1"<<std::endl;
                break;
            case 2:
                this->sprite.setTextureRect(sf::IntRect(164, 47, 60, 81));
                //std::cout<<"Attack2 frame 2"<<std::endl;
                break;
            case 3:
                this->sprite.setTextureRect(sf::IntRect(292, 47, 60, 81));
                //std::cout<<"Attack2 frame 3"<<std::endl;
                break;
        }
    }
    else if(this->animationType == 3)
    {
        switch(this->frame)
        {
            case 1:
                this->sprite.setTextureRect(sf::IntRect(35, 47, 60, 81));
                //std::cout<<"Attack3 frame 1"<<std::endl;
                break;
            case 2:
                this->sprite.setTextureRect(sf::IntRect(178, 47, 60, 81));
                //std::cout<<"Attack3 frame 2"<<std::endl;
                break;
            case 3:
                this->sprite.setTextureRect(sf::IntRect(301, 47, 60, 81));
                //std::cout<<"Attack3 frame 3"<<std::endl;
                break;
            case 4:
                this->sprite.setTextureRect(sf::IntRect(423, 47, 60, 81));
                //std::cout<<"Attack3 frame 4"<<std::endl;
                break;
        }
    }
    else if(this->animationType == 4)
    {
        switch(this->frame)
        {
            case 1:
                this->sprite.setTextureRect(sf::IntRect(35, 47, 70, 81));
                //std::cout<<"Dead frame 1"<<std::endl;
                break;
            case 2:
                this->sprite.setTextureRect(sf::IntRect(163, 47, 70, 81));
                //std::cout<<"Dead frame 2"<<std::endl;
                break;
            case 3:
                this->sprite.setTextureRect(sf::IntRect(290, 47, 75, 81));
                //std::cout<<"Dead frame 3"<<std::endl;
                break;
        }
    }
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

void Player::setAttack2()
{
    this->sprite.setTexture(this->attack2Texture);
    this->animationType = 2;
    this->frame = 1;
    this->maxFrame = 3;
    this->animationTimer = 0;
}

void Player::setAttack3()
{
    this->sprite.setTexture(this->attack3Texture);
    this->animationType = 3;
    this->frame = 1;
    this->maxFrame = 4;
    this->animationTimer = 0;
}

void Player::setDead()
{
    this->sprite.setTexture(this->deadTexture);
    this->animationType = 4;
    this->frame = 1;
    this->maxFrame = 3;
    this->animationTimer = 0;
}

void Player::attack1()
{
    this->setAttack1();
}

void Player::attack2()
{
    this->setAttack2();
}

void Player::attack3()
{
    this->setAttack3();
}

void Player::dead()
{
    this->setDead();
}