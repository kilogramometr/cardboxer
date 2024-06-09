#pragma once
#include "Node.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Game : public Node
{
private:
    std::list<Card *> *library;
    std::list<Enemy *> *enemies;
    Player *player;
    Enemy *enemy;

    Button *restartButton;
    Button *returnButton;
    Button *playerDeck;
    Button *playerDiscard;
    Button *offensiveButton;
    Button *defensiveButton;
    Button *drawButton;
    
    Card hoverCard;
    Card lastPlayed;
    Card *nextPlay = nullptr;
    bool playerTurn;
    bool moved;
    bool choose;
    bool playerDead = false;
    bool animationEnd = false;
    bool enemyDead = false;
    bool chain = false;

    sf::Clock timer;
    sf::Vector2f lastPos;
    std::list<Card *>::iterator lastMoved;
        
    void onDraw(sf::RenderTarget& target, sf::Transform& transform);

    void onUpdate(sf::Vector2f mousePos);
    void turn();
    void hideCards();
    void showCards();
    void updateCards();
    void showButtons();
    void hideButtons();
    void updateLastPlayed(Card card);
    void updateHoverCard();
    void randomEnemy();
    void killEnemy();
    void killPlayer();
public:
    Game(std::list<Card *> *library, std::list<Enemy *> *enemies);

    void resolveCard(Card *card, Boxer *source, bool offensive);
    void randomisePlayerDeck(std::list<Card *> *library);
    void setEnemy(Enemy enemy);
    
    int onButtonClick(sf::Vector2f mousePosition);
};

