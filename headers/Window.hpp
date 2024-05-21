#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <headers/Node.hpp>
#include <headers/Card.hpp>

class Window : public sf::RenderWindow
{
    sf::Vector2f resolution;
    /* Scene */ Node *menu;
    /* Scene */ Node *game;
    /* Scene */ Node *Scene;
    // QGraphicsView  *view;
    std::list<Card> library;
    // QJsonObject config;

    bool loadLibrary(std::string path);
    void changeResolution(sf::Vector2f resolution);
    void changeScene(Node *scene);
    void createMenu();
    void drawScene();

public:
    Window(sf::Vector2f resolution, std::string title);
    void loop();
// public slots:
    // void gameOver();
    // void newGame();
    // void backToMenu();
    // void exit();

};

