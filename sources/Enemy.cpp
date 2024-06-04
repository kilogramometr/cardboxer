#include "../headers/Enemy.hpp"

Enemy::Enemy(): Boxer() {}

Enemy::Enemy(Json::Value enemy, std::list<Card *>& library)
    : Boxer()
{

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
        for (int i = 0; i < size; i++)
        {
            std::string name = enemy["actions"][i]["cardName"].asString();
            auto card = std::find_if(library.begin(), library.end(), [name](Card* _card){ return (*_card == name); });
            if (card != library.end())
                this->addToDeck(*card);
            else
                throw 41;
            
            /* search through window->library for the card here */
            this->probabilities.emplace_back(enemy["actions"][i]["probability"].asFloat());
        }  
    } 

}