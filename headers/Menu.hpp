#pragma once
#include "Node.hpp"
#include "Button.hpp"

class Menu : public Node
{
private:
    Button *gameButton;
    Button *cardsLibraryButton;
    Button *exitButton;

    sf::Text text;
    sf::Font font;
    // QPushButton *gameButton;
    // QPushButton *exitButton;

    void onDraw(sf::RenderTarget& target, sf::Transform& transform);
public:
    Menu();
// signals:
//     void exit();
//     void newGame();
};

