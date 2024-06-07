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

    void onUpdate();

    
public:
    Game();

    void setEnemy(Enemy enemy);
    void killEnemy();
    void killPLayer();
    
    int onButtonClick(sf::Vector2f mousePosition);
};
