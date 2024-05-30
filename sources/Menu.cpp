#include "../headers/Menu.hpp"

Menu::Menu()
{
    this->gameButton = new Button(sf::Vector2f(300, 250), sf::Vector2f(200, 80), sf::Vector2f(40, -10), 65, sf::Color::Green, "Game", 1);
    this->cardsLibraryButton = new Button(sf::Vector2f(300, 360), sf::Vector2f(200, 80), sf::Vector2f(40, -10), 65, sf::Color::Blue, "Cards", 4);
    this->exitButton = new Button(sf::Vector2f(300, 470), sf::Vector2f(200, 80), sf::Vector2f(55, -10), 65, sf::Color::Red, "Exit", 2);
    // this->gameButton = new Button();
    this->appendChild(this->gameButton);
    this->appendChild(this->cardsLibraryButton);
    this->appendChild(this->exitButton);
    //this->exitButton->setPosition({0, 0});
    // this->appendChild(this->gameButton);
    
    // this->gameButton = new QPushButton();
    // this->exitButton = new QPushButton();
}

void Menu::onDraw(sf::RenderTarget& target) {}