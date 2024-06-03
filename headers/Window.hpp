#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Node.hpp"
#include "Card.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "CardLibrary.hpp"
#include "Enemy.hpp"

class Window : public sf::RenderWindow
{
    sf::Vector2f resolution;
    sf::RectangleShape *backGround;
    /* Scene */ Menu *menu;
    /* Scene */ Node *game;
    /* Scene */ Node *cardLibrary;
    /* Scene */ Node *Scene;
    // QGraphicsView  *view;
    std::list<Card *> library;
    std::list<Enemy *> enemies;
    // QJsonObject config;

    // bool loadLibrary(std::string path);
    // void changeResolution(sf::Vector2f resolution);
    // void changeScene(Node *scene);
    // void createMenu();
    bool loadLibrary();
    bool loadEnemies();

    void drawScene();
    void setCurrentScene(Node *node);

    //Mouse position
    sf::Vector2f mousePosition;
    bool mouseHold;
    void updateMousePosition();
    void checkMouseHold();

    void checkClicks();

public:
    Window(sf::Vector2f resolution, std::string title);
    void loop();
// public slots:
    // void gameOver();
    // void newGame();
    // void backToMenu();
    // void exit();

};
