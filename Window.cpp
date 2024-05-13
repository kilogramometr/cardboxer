#include "Window.h"
Window::Window(QSize resolution)
{
    // set resolution
    this->resolution = resolution;
    // create scene and view
    this->createMenu();
    this->view  = new QGraphicsView();
    // set view options
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->changeScene(this->menu); // set current scene, by default menu
    this->view->setMinimumSize(this->resolution);
    this->view->setSceneRect(0, 0, this->resolution.width() - 5,  this->resolution.height() - 5);
    this->view->setBackgroundBrush(Qt::black);
    this->view->show();
    this->setWindowTitle("");
}

/*
 * UTILITY
 */

void Window::changeResolution(QSize resolution)
/* set new resolution */
{
    this->resolution = resolution;
    this->view->setMinimumSize(this->resolution);
}

void Window::changeScene(QGraphicsScene *scene)
/* change currently shown scene */
{
    this->view->setScene(scene);
}

/*
 * INIT
 */

void Window::createMenu()
/* set up Menu scene to be shown */
{
    this->menu = new QGraphicsScene();
}

bool Window::loadLibrary(QString path)
/* load global library of cards for use during game */
{
    // TODO: Load cards from jsons as json objects into this->library (list of cards)
    return true;
}

/*
 * SIGNALS
 */

void Window::newGame()
/* create new game and set it as current scene */
{
    this->game = new Game();
    // TODO: Connect game's backToMenu signal to Window's slot
    this->changeScene(this->game);
}

void Window::backToMenu()
{
    // TODO: Remove game's connection to Window's slots
    this->changeScene(this->menu);
    delete this->game;
}

