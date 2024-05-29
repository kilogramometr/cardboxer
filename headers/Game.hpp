#pragma once
#include "Node.hpp"

class Game : public Node
{
private:

    void onDraw(sf::RenderTarget& target);
public:
    Game();

};
