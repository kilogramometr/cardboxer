#pragma once
#include "Node.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Game : public Node
{
private:
    std::list<Card *> *library;
    Player *player;
    Enemy *enemy;

    Button *restartButton;
    Button *returnButton;
    Button *playerDeck;
    Button *playerDiscard;
    
    Card hoverCard;
    Card lastPlayed;
    bool playerTurn;
    bool moved = false;
    sf::Clock timer;
    sf::Vector2f lastPos;
    std::list<Card *>::iterator lastMoved;
    
    void onDraw(sf::RenderTarget& target, sf::Transform& transform);

    void onUpdate(sf::Vector2f mousePos);
    void turn();
public:
    Game(std::list<Card *> *library);

    void resolveCard(Card *card, Boxer *source, bool offensive);
    void randomisePlayerDeck(std::list<Card *> *library);
    void setEnemy(Enemy enemy);
    void killEnemy();
    void killPlayer();
    
    int onButtonClick(sf::Vector2f mousePosition);
    void hideCards();
    void showCards();
    void updateCards();
};
