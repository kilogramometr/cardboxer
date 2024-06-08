#include "../headers/Enemy.hpp"
#include <iostream>
Enemy::Enemy(): Boxer()
{
    this->construct();
}

Enemy::Enemy(Json::Value enemy, std::list<Card *>& library)
    : Boxer()
{
    this->construct();


    if (enemy["name"].isNull()) { throw 10; }
    else
    {
        this->name.setString(enemy["name"].asString());
    }

    if (enemy["hp"].isNull()) { throw 20; }
    else 
    {
        this->setHealth(enemy["hp"].asInt());
        this->setMaxHealth(enemy["hp"].asInt());
    }

    if (enemy["texture"].isNull()) { throw 30; }
    /* load texture or throw error if not exists */
    else
    {
        this->texture = new sf::Texture();
        std::string path = "./res/textures/" + enemy["texture"]["file"].asString();
        if(!this->texture->loadFromFile(path))
            throw 31;
        this->setTexture(*this->texture);

        this->frames = enemy["texture"]["frames"].asInt();
        this->frameWidth = enemy["texture"]["frameWidth"].asInt();
        this->frameHeight = enemy["texture"]["frameHeight"].asInt();
        this->framePos = { enemy["texture"]["x"].asFloat(), enemy["texture"]["y"].asFloat() };
    }

    if (!enemy["actions"].isArray()) { throw 40; }
    else
    {
        int size = enemy["actions"].size();
        std::cerr<<"Number of actions: "<<size<<"\n";
        for (int i = 0; i < size; i++)
        {
            std::string name = enemy["actions"][i]["cardName"].asString();
            auto card = std::find_if(library.begin(), library.end(), [name](Card* _card){ return (*_card == name); });
            if (card != library.end())
            {
                // this->deck->emplace_back(new Card(**card));
                this->deck.emplace_back(new Card(**card));
                // this->addToDeck(*card);
            }
            else
                throw 41;
            
            /* search through window->library for the card here */
            this->probabilities.emplace_back(enemy["actions"][i]["probability"].asFloat());
        }  
    } 
    
    auto it_d = this->deck.begin();
    auto it_p = this->probabilities.begin();

    for (; it_d != this->deck.end() && it_p != this->probabilities.end(); ++it_d, ++it_p)
    {
        std::cerr<<(*it_d)->getName()<<" "<<(*it_p)<<"\n";
    }
}    

void Enemy::construct()
{
    this->healthbar = new Healthbar(1);
    this->appendChild(this->healthbar);

    //Setting health to 80%
    this->healthbar->setHealth(80);

    this->shield = new Shield(1);
    this->appendChild(this->shield);

    this->loadSprites();

    this->setIdle();
}

void Enemy::loadSprites()
{
    this->sam_idleTexture.loadFromFile("../res/textures/Samurai/Idle.png");
    this->sam_attack1Texture.loadFromFile("../res/textures/Samurai/Attack_1.png");
    this->sam_attack2Texture.loadFromFile("../res/textures/Samurai/Attack_2.png");
    this->sam_attack3Texture.loadFromFile("../res/textures/Samurai/Attack_3.png");
    this->sam_deadTexture.loadFromFile("../res/textures/Samurai/Dead.png");

    this->setScale(sf::Vector2f(-1.5, 1.5));
    this->setPosition(sf::Vector2f(600, 320));
}

void Enemy::onDraw(sf::RenderTarget &target, sf::Transform& transform)
{
    target.draw(*this);
}

void Enemy::onUpdate()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        this->setAttack1();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        this->setAttack2();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        this->setAttack3();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        this->setDead();

    this->animate();
}

void Enemy::animate()
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
    this->setAnimationFrame();
}

void Enemy::setAnimationFrame()
{
    if(this->animationType == 0)
    {
        switch(this->frame)
        {
            case 1:
                this->setTextureRect(sf::IntRect(41, 47, 60, 81));
                break;
            case 2:
                this->setTextureRect(sf::IntRect(169, 47, 60, 81));
                break;
            case 3:
                this->setTextureRect(sf::IntRect(297, 47, 60, 81));
                break;
            case 4:
                this->setTextureRect(sf::IntRect(425, 47, 60, 81));
                break;
            case 5:
                this->setTextureRect(sf::IntRect(553, 47, 60, 81));
                break;
            case 6:
                this->setTextureRect(sf::IntRect(681, 47, 60, 81));
                break;
        }
    }
    else if(this->animationType == 1)
    {
        switch(this->frame)
        {
            case 1:
                this->setTextureRect(sf::IntRect(23, 47, 60, 81));
                break;
            case 2:
                this->setTextureRect(sf::IntRect(152, 47, 60, 81));
                break;
            case 3:
                this->setTextureRect(sf::IntRect(280, 47, 60, 81));
                break;
            case 4:
                this->setTextureRect(sf::IntRect(408, 47, 60, 81));
                break;
            case 5:
                this->setTextureRect(sf::IntRect(536, 47, 101, 81));
                break;
            case 6:
                this->setTextureRect(sf::IntRect(664, 47, 60, 81));
                break;
        }
    }
    else if(this->animationType == 2)
    {
        switch(this->frame)
        {
            case 1:
                this->setTextureRect(sf::IntRect(30, 47, 60, 81));
                break;
            case 2:
                this->setTextureRect(sf::IntRect(155, 47, 60, 81));
                break;
            case 3:
                this->setTextureRect(sf::IntRect(286, 47, 101, 81));
                break;
            case 4:
                this->setTextureRect(sf::IntRect(414, 47, 60, 81));
                break;
        }
    }
    else if(this->animationType == 3)
    {
        switch(this->frame)
        {
            case 1:
                this->setTextureRect(sf::IntRect(22, 47, 60, 81));
                break;
            case 2:
                this->setTextureRect(sf::IntRect(152, 47, 60, 81));
                break;
            case 3:
                this->setTextureRect(sf::IntRect(280, 47, 101, 81));
                break;
        }
    }
    else if(this->animationType == 4)
    {
        switch(this->frame)
        {
            case 1:
                this->setTextureRect(sf::IntRect(25, 47, 60, 81));
                break;
            case 2:
                this->setTextureRect(sf::IntRect(152, 47, 60, 81));
                break;
            case 3:
                this->setTextureRect(sf::IntRect(285, 47, 101, 81));
                break;
        }
    }
}

void Enemy::setIdle()
{
    this->setTexture(this->sam_idleTexture);
    this->frame = 1;
    this->maxFrame = 6;
    this->animationTimer = 0;
    this->animationType = 0;
}

void Enemy::setAttack1()
{
    this->setTexture(this->sam_attack1Texture);
    this->frame = 1;
    this->maxFrame = 6;
    this->animationTimer = 0;
    this->animationType = 1;
}

void Enemy::setAttack2()
{
    this->setTexture(this->sam_attack2Texture);
    this->frame = 1;
    this->maxFrame = 4;
    this->animationTimer = 0;
    this->animationType = 2;
}

void Enemy::setAttack3()
{
    this->setTexture(this->sam_attack3Texture);
    this->frame = 1;
    this->maxFrame = 3;
    this->animationTimer = 0;
    this->animationType = 3;
}

void Enemy::setDead()
{
    this->setTexture(this->sam_deadTexture);
    this->frame = 1;
    this->maxFrame = 3;
    this->animationTimer = 0;
    this->animationType = 4;
}