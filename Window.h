#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QList>
#include <Card.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QJsonObject>
#include <Game.h>
#include <Menu.h>
class Window : public QMainWindow
{
    Q_OBJECT

    QSize resolution;
    /* QGraphicsScene */ Menu *menu;
    QGraphicsScene *game;
    QGraphicsView  *view;
    QList<Card> library;
    QJsonObject config;

    bool loadLibrary(QString path);
    void changeResolution(QSize resolution);
    void changeScene(QGraphicsScene *scene);
    void createMenu();

public:
    Window(QSize resolution = {800, 600});

public slots:
    // void gameOver();
    void newGame();
    void backToMenu();
    void exit();

};

#endif // WINDOW_H
