#pragma once
#include "Node.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Game : public Node
{
private:
    Player *player;
    Enemy *enemy;

    Button *returnButton;
    void onDraw(sf::RenderTarget& target, sf::Transform& transform);
public:
    Game();

};
