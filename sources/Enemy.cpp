#include "../headers/Enemy.hpp"
#include <iostream>
Enemy::Enemy(): Boxer()
{
    this->healthbar = new Healthbar(1);
    this->appendChild(this->healthbar);

    //Setting health to 80%
    this->healthbar->setHealth(80);

    this->shield = new Shield(1);
    this->appendChild(this->shield);

    this->loadSprites();
}

Enemy::Enemy(Json::Value enemy, std::list<Card *>& library)
    : Boxer()
{
    this->healthbar = new Healthbar(1);
    this->appendChild(this->healthbar);

    //Setting health to 80%
    this->healthbar->setHealth(80);

    this->loadSprites();


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

void Enemy::loadSprites()
{
    this->sam_idleTexture.loadFromFile("../res/textures/Samurai/Idle.png");
    this->sprite.setTexture(this->sam_idleTexture);
}

void Enemy::onDraw(sf::RenderTarget &target, sf::Transform& transform)
{
    //target.draw(this->sprite);
}