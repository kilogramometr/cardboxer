#pragma once
#include "Node.hpp"
#include "Button.hpp"

class Game : public Node
{
private:
    Button *returnButton;
    void onDraw(sf::RenderTarget& target);
public:
    Game();

};
