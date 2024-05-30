#pragma once
#include "Node.hpp"
#include "CardAction.hpp"
#include <jsoncpp/json/json.h>

class Card : public Node, public sf::Sprite
{
    CardAction *defensiveAction;
    CardAction *offensiveAction;
    std::string desc;
    std::string originalDesc;
    sf::Texture *texture;
    sf::Font *font;
    sf::Text *name;
    sf::Text *description;

    // std::string name;

    void onDraw(sf::RenderTarget& target) override;
    void setName(std::string name, int size);
    void setDesc(std::string descritpion, int size);
    void updateDesc();
    void setFont();
    
public:
    Card(Json::Value card);
    // void load(/* json object card */);
};

