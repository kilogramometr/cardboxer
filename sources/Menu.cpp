#include "../headers/Menu.hpp"

Menu::Menu()
{
    this->gameButton = new Button(sf::Vector2f(300, 250), sf::Vector2f(200, 100), sf::Vector2f(40, 0), 65, sf::Color::Green, "Game", "Game Button Clicked!");
    this->exitButton = new Button(sf::Vector2f(300, 400), sf::Vector2f(200, 100), sf::Vector2f(55, 0), 65, sf::Color::Red, "Exit", "Exit Button Clicked!");
    // this->gameButton = new Button();
    this->appendChild(this->gameButton);
    this->appendChild(this->exitButton);
    //this->exitButton->setPosition({0, 0});
    // this->appendChild(this->gameButton);
    
    // this->gameButton = new QPushButton();
    // this->exitButton = new QPushButton();
}

void Menu::onDraw(sf::RenderTarget& target) {}