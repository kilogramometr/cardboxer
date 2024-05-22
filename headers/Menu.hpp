#pragma once
#include "Node.hpp"
#include "Button.hpp"

class Menu : public Node
{
private:
    Button *gameButton;
    Button *exitButton;
    // QPushButton *gameButton;
    // QPushButton *exitButton;

    void onDraw(sf::RenderTarget& target);
public:
    Menu();
// signals:
//     void exit();
//     void newGame();
};

