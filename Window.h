#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QList>
#include <Card.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QJsonObject>

class Window : public QMainWindow
{
    Q_OBJECT

    QSize resolution;
    // int TILE_SIZE = 100;
    // int MAP_SIZE = 7;
    QGraphicsScene *menu;
    QGraphicsView  *view;
    QList<Card> library;
    QJsonObject config;

    bool loadLibrary();
    void changeResolution(QSize resolution);
    void changeScene(QGraphicsScene *scene);
    void newGame();

public:
    Window(QSize resolution = {800, 600});

public slots:
    // void gameOver();
};

#endif // WINDOW_H
