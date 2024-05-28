#include "../headers/Card.hpp"
#include <fstream>

Card::Card(Json::Value card) 
/* Card constuctor */
{
    this->font = new sf::Font();
    this->name = new sf::Text();
    this->description = new sf::Text();
    (card["name"].isNull()) ? throw 1 : this->name->setString(card["name"].asString());
    (card["description"].isNull()) ? throw 2 : this->desc = card["description"].asString(); 

    /* load defensive action if exists */
    if (!card["defensive"].isNull())
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

    if (card["texture"].isNull()) { throw 30; }
    /* load texture or throw error if not exists */
    else
    {
        this->texture = new sf::Texture();
        std::string path = "./res/textures/" + card["texture"]["file"].asString();
        if(!this->texture->loadFromFile(path))
            throw 31;
        this->setTexture(*this->texture);
        this->setTextureRect({card["texture"]["x"].asInt(), card["texture"]["y"].asInt(), card["texture"]["w"].asInt(), card["texture"]["h"].asInt()});
    }
}

void Card::onDraw(sf::RenderTarget& target) {}

void Card::setFont()
{
    this->font = new sf::Font();
    this->font->loadFromFile("./res/fonts/pixellettersfull.ttf");
}

void Card::setText(sf::Vector2f position, std::string buttonText, int textSize, sf::Vector2f textOffset)
{
    this->name = new sf::Text();
    this->name->setFont(*this->font);
    this->name->setCharacterSize(textSize);
    this->name->setFillColor(sf::Color::White);
    this->name->setString(buttonText);
    this->name->setPosition(position);
    this->name->move(textOffset);
}