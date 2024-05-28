#pragma once
#include "Node.hpp"
#include "CardAction.hpp"
#include <jsoncpp/json/json.h>

class Card : public Node, public sf::Sprite
{
    CardAction *defensiveAction;
    CardAction *offensiveAction;
    std::string desc;
    sf::Texture *texture;
    sf::Font *font;
    sf::Text *name;
    sf::Text *description;

    // std::string name;

    void onDraw(sf::RenderTarget& target) override;

    void setText(sf::Vector2f position, std::string buttonText, int textSize, sf::Vector2f textOffset);
    void setFont();
    
public:
    Card(Json::Value card);
    // void load(/* json object card */);
};

