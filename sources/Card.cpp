#include "../headers/Card.hpp"
#include <fstream>
#include <iostream>

Card::Card() {}

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
    
    this->setFont();
    (card["name"].isNull()) ? throw 1 : this->setName(card["name"].asString(), 40);
    (card["description"].isNull()) ? throw 2 : this->setDesc(card["description"].asString(), 22); 
    // std::cerr<<"\n end of constructor\n";
    // std::cerr<<this->desc<<std::endl<<this->originalDesc<<std::endl;
}


void Card::setFont()
{
    this->font = new sf::Font();
    this->font->loadFromFile("./res/fonts/pixellettersfull.ttf");
}

void Card::setName(std::string name, int size)
{
    this->originalName = name;
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
    
    pos = this->desc.find("$om");
    if (pos != -1) 
        { this->desc.replace(pos, 3, std::to_string(this->offensiveAction->getMaxHealthMod())); }
    
    pos = this->desc.find("$og");
    if (pos != -1) 
        { this->desc.replace(pos, 3, std::to_string(this->offensiveAction->getGuardMod())); }
    
    pos = this->desc.find("$dh");
    if (pos != -1) 
        { this->desc.replace(pos, 3, std::to_string(this->defensiveAction->getHealthMod())); }
    
    pos = this->desc.find("$dm");
    if (pos != -1) 
        { this->desc.replace(pos, 3, std::to_string(this->defensiveAction->getMaxHealthMod())); }
    
    pos = this->desc.find("$dg");
    if (pos != -1) 
        { this->desc.replace(pos, 3, std::to_string(this->defensiveAction->getGuardMod())); }

    this->calcDescWrap();
    this->description->setString(this->desc);
}

void Card::onDraw(sf::RenderTarget& target, sf::Transform& transform) 
{
    this->updateDesc();
    this->calcNameWrap();
    this->updateTextPosition();
    target.draw(*this, transform);
    target.draw(*this->name, transform);
    target.draw(*this->description, transform);
}

void Card::updateTextPosition()
{
    auto position = this->getPosition();
    auto bounds = this->getLocalBounds();
    auto scale = this->getScale();
    
    float margin = 15*scale.x;

    this->name->setScale(scale);
    this->name->setPosition(position.x + margin, position.y);

    float middle = (bounds.height*scale.x)/ 2 + position.y;
    // std::cerr<<position.x<<" "<<position.y<<"\n";
    // std::cerr<<bounds.height<<std::endl<<scale.y<<std::endl<<std::endl;
    this->description->setScale(scale);
    this->description->setPosition(position.x + margin, middle - margin);
}

void Card::calcDescWrap()
{
    float letterSpacing = this->description->getLetterSpacing();
    float characterSize = this->description->getCharacterSize();
    float cardWidth = this->getTextureRect().width;
    float currentLine = 0;
    int lastSpace = 0;

    for (int i = 0; i < this->desc.length(); i++)
    {
        if (this->desc[i] == '\n')
        {
            currentLine = 0;
            continue;
        }

        if (this->desc[i] == ' ')
            lastSpace = i;

        sf::Glyph glyph = this->font->getGlyph(this->desc[i], characterSize, false);
        float glyphWidth = glyph.advance;
        // std::cerr<<currentLine<<" "<<glyphWidth<<" "<<currentLine+glyphWidth<<std::endl;
      
        if ((currentLine + glyphWidth + 2*letterSpacing) > cardWidth)
        { 
            currentLine = 0;
            int pos; std::string insert;
            if (i - lastSpace > 10)
                { pos = i; insert = "-\n"; }
            else
                { pos = lastSpace+1; insert = "\n"; }
            this->desc.insert(pos, insert); 
        }
        else
            currentLine += glyphWidth + letterSpacing; 
    }
}

void Card::calcNameWrap()
{
    float letterSpacing = this->name->getLetterSpacing();
    float characterSize = this->name->getCharacterSize();
    float cardWidth = this->getTextureRect().width;
    float currentLine = 0;
    int lastSpace = 0;
    std::string name = this->originalName;

    for (int i = 0; i < name.length(); i++)
    {
        if (name[i] == '\n')
        {
            currentLine = 0;
            continue;
        }

        if (name[i] == ' ')
            lastSpace = i;

        sf::Glyph glyph = this->font->getGlyph(name[i], characterSize, false);
        float glyphWidth = glyph.advance;

        if ((currentLine + glyphWidth + 2*letterSpacing) > cardWidth)
        { 
            currentLine = 0;
            int pos; std::string insert;
            if (i - lastSpace > 10)
                { pos = i; insert = "-\n"; }
            else
                { pos = lastSpace+1; insert = "\n"; }
            name.insert(pos, insert); 
        }
        else
            currentLine += glyphWidth + letterSpacing; 
    }

    this->name->setString(name);
}


std::string Card::getName() { return this->name->getString(); }