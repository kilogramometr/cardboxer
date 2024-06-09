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

    this->font.loadFromFile("./res/fonts/pixellettersfull.ttf");
    this->text.setFont(this->font);
    this->text.setPosition(sf::Vector2f(130, -30));
    this->text.setCharacterSize(150);
    this->text.setFillColor(sf::Color::Black);
    this->text.setString("Cardboxer");
}

void Menu::onDraw(sf::RenderTarget& target, sf::Transform& transform)
{
    target.draw(this->text, transform);
}