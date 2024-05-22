#include "../headers/Menu.hpp"

Menu::Menu()
{
    this->exitButton = new Button("Buton", {200,100}, 18, "./res/fonts/ARIAL.ttf");
    // this->gameButton = new Button();
    this->appendChild(this->exitButton);
    this->exitButton->setPosition({0, 0});
    // this->appendChild(this->gameButton);
    
    // this->gameButton = new QPushButton();
    // this->exitButton = new QPushButton();
}

void Menu::onDraw(sf::RenderTarget& target) {}