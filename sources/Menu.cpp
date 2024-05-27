#include "../headers/Menu.hpp"

Menu::Menu()
{
    this->gameButton = new Button(sf::Vector2f(100, 100), sf::Vector2f(200, 100), sf::Vector2f(20, 15), 55, sf::Color::Green, "Game");
    this->exitButton = new Button(sf::Vector2f(300, 300), sf::Vector2f(200, 100), sf::Vector2f(20, 15), 55, sf::Color::Red, "Exit");
    // this->gameButton = new Button();
    this->appendChild(this->gameButton);
    this->appendChild(this->exitButton);
    //this->exitButton->setPosition({0, 0});
    // this->appendChild(this->gameButton);
    
    // this->gameButton = new QPushButton();
    // this->exitButton = new QPushButton();
}

void Menu::onDraw(sf::RenderTarget& target) {}