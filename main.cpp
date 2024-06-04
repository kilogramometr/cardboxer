// #include "Window.h"
// #include "qapplication.h"

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);
//     Window *window = new Window();
//     delete window;
//     return app.exec();
// }

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "./headers/Window.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    Window *window;
    try { window = new Window(sf::Vector2f(800, 600), "Title"); }
    catch (int e) 
    { 
        if (e == 0)
            std::cerr<<"Critical Error: unable to load card library, aborting...\n";
        else if (e == 1)
            std::cerr<<"Critical Error: unable to load enemy list, aborting...\n";
        else
            std::cerr<<"Critical Error: unidentified error #"+std::to_string(e)+" occured, aborting...\n"; 
        return 0; 
    };
        
    while(window->isOpen())
    {
        window->loop();
        // window.display();
        // window.draw(*shape);
    }
    // window.reset();
    delete window;
    return 0;
}