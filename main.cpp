// #include "Window.h"
// #include "qapplication.h"

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);
//     Window *window = new Window();
//     delete window;
//     return app.exec();
// }

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <headers/Window.hpp>
#include <memory>

int main(int argc, char *argv[])
{
    std::unique_ptr<Window> window = std::make_unique<Window>();
    while(window->isOpen())
    {
        sf::Event event;
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                default:
                    break;
            }
        }
        window->loop();
    }
    window.reset();
    return 0;
}