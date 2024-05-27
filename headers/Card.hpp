#pragma once
#include "Node.hpp"
#include "CardAction.hpp"
#include <jsoncpp/json/json.h>

class Card : public Node, public sf::Sprite
{

    CardAction *defensiveAction;
    CardAction *offensiveAction;
    sf::Texture texture;
    // sf::Font font;
    // sf::Text text;
    // std::string name;

    void onDraw(sf::RenderTarget& target) override;

public:
    Card(Json::Value card);
    // void load(/* json object card */);
};

