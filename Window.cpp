#include "Window.h"
Window::Window(QSize resolution)
{
    // set resolution
    this->resolution = resolution;
    // create scene and view
    this->menu = new QGraphicsScene();
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

void Window::changeResolution(QSize resolution)
{
    this->resolution = resolution;
    this->view->setMinimumSize(this->resolution);
}

void Window::changeScene(QGraphicsScene *scene)
{
    this->view->setScene(scene);
}

bool Window::loadLibrary(QString path)
{
    return true;
}
