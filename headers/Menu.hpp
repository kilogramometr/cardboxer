#pragma once
#include <headers/Button.hpp>

class Menu : public Node
{
private:
    Button *gameButton;
    Button *exitButton;
    // QPushButton *gameButton;
    // QPushButton *exitButton;
public:
    Menu();
// signals:
//     void exit();
//     void newGame();
};

