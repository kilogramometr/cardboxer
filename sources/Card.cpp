#include "../headers/Card.hpp"
#include <fstream>
#include <iostream>
Card::Card(Json::Value card) 
/* Card constuctor */
{


    if (!card["defensive"].isNull())
    /* load defensive action if exists */
    {   
        this->defensiveAction = new CardAction(
            false,
            (card["defensive"]["health"].isNull()) ? throw 11 : card["health"].asInt(),
            (card["defensive"]["maxHealth"].isNull()) ? throw 12 : card["maxHealth"].asInt(),
            (card["defensive"]["guard"].isNull()) ? throw 13 : card["guard"].asInt()
        );
    }

    if (!card["offensive"].isNull())
    /* load offensive action if exists */
    {
        this->offensiveAction = new CardAction{
            true,
            (card["offensive"]["health"].isNull()) ? throw 21 : card["health"].asInt(),
            (card["offensive"]["maxHealth"].isNull()) ? throw 22 : card["maxHealth"].asInt(),
            (card["offensive"]["guard"].isNull()) ? throw 23 : card["guard"].asInt()
        };
    }

    // if (card["texture"].isNull()) { throw 30; }
    // /* load texture or throw error if not exists */
    // else
    // {
    //     this->texture = new sf::Texture();
    //     std::string path = "./res/textures/" + card["texture"]["file"].asString();
    //     if(!this->texture->loadFromFile(path))
    //         throw 31;
    //     this->setTexture(*this->texture);
    //     this->setTextureRect({card["texture"]["x"].asInt(), card["texture"]["y"].asInt(), card["texture"]["w"].asInt(), card["texture"]["h"].asInt()});
    // }
    
    this->setFont();
    (card["name"].isNull()) ? throw 1 : this->setName(card["name"].asString(), 20);
    (card["description"].isNull()) ? throw 2 : this->setDesc(card["description"].asString(), 20); 
    // std::cerr<<"\n end of constructor\n";
    // std::cerr<<this->desc<<std::endl<<this->originalDesc<<std::endl;
}

void Card::onDraw(sf::RenderTarget& target) {}

void Card::setFont()
{
    this->font = new sf::Font();
    this->font->loadFromFile("./res/fonts/pixellettersfull.ttf");
}

void Card::setName(std::string name, int size)
{
    this->name = new sf::Text();
    this->name->setString(name);
    this->name->setCharacterSize(size);
    this->name->setFont(*this->font);
}

void Card::setDesc(std::string desc, int size)
{
    this->description = new sf::Text();
    this->originalDesc = desc;
    this->updateDesc();
    this->description->setCharacterSize(size);
    this->description->setFont(*this->font);
}

void Card::updateDesc()
/* update description with values*/
{
    this->desc = this->originalDesc;

    int pos = this->desc.find("$oh");
    if (pos != -1) 
        { this->desc.replace(pos, 3, std::to_string(this->offensiveAction->getHealthMod())); }
    
    // if (this->desc.find("$om") != -1) 
    //     { this->desc.replace(this->desc.find("$om"), 3, std::to_string(this->offensiveAction->getMaxHealthMod())); }
    
    // if ((index = this->desc.find("$og")) != -1) 
    //     { this->desc.replace(index, 3, std::to_string(this->offensiveAction->getGuardMod())); }
    
    // if ((index = this->desc.find("$dh")) != -1) 
    //     { this->desc.replace(index, 3, std::to_string(this->defensiveAction->getHealthMod())); }
    
    // if ((index = this->desc.find("$dm")) != -1) 
    //     { this->desc.replace(index, 3, std::to_string(this->defensiveAction->getMaxHealthMod())); }
    
    // if ((index = this->desc.find("$dg")) != -1) 
    //     { this->desc.replace(index, 3, std::to_string(this->defensiveAction->getGuardMod())); }
    this->description->setString(this->desc);
}