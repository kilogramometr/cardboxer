#include "../headers/Card.hpp"

Card::Card(Json::Value card) 
{
    if (!card["defensive"].isNull())
    {
        this->defensiveAction = new CardAction(
            false,
            (card["health"].isNull()) ? throw 1 : card["health"].asInt(),
            (card["maxHealth"].isNull()) ? throw 2 : card["maxHealth"].asInt(),
            (card["guard"].isNull()) ? throw 3 : card["guard"].asInt()
        );
    }
}

void Card::onDraw(sf::RenderTarget& target) {}