#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>

class Menu : public QGraphicsScene
{
private:
    QPushButton *gameButton;
    QPushButton *exitButton;
public:
    Menu();
signals:
    void exit();
    void newGame();
};

#endif // MENU_H
