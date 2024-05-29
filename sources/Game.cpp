#include "../headers/Game.hpp"

Game::Game()
{
    this->player = new Player;
    this->appendChild(this->player);

    this->enemy = new Enemy;
    this->appendChild(this->enemy);

    this->returnButton = new Button(sf::Vector2f(600, 0), sf::Vector2f(200, 100), sf::Vector2f(30, 0), 65, sf::Color::Red, "Return", 3);
    this->appendChild(this->returnButton);
}

void Game::onDraw(sf::RenderTarget& target) {}
