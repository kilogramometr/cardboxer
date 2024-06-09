#include "../headers/Game.hpp"

Game::Game()
{
    this->player = new Player;
    this->appendChild(this->player);

    this->enemy = new Enemy(0);
    this->appendChild(this->enemy);

    this->returnButton = new Button(sf::Vector2f(300, 0), sf::Vector2f(200, 50), sf::Vector2f(45, -10), 50, sf::Color::Red, "Return", 3);
    this->appendChild(this->returnButton);
}

void Game::onDraw(sf::RenderTarget& target, sf::Transform& transform) {}

void Game::onUpdate()
{
    //std::cout<<"Game screen update"<<std::endl;
}

void Game::setEnemy(Enemy enemy) { this->enemy = &enemy; }
void Game::killEnemy() { delete this->player; };
void Game::killPLayer() { delete this->enemy; };


int Game::onButtonClick(sf::Vector2f mousePosition)
{
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        int code = (*i)->buttonClick(mousePosition);
        if (code != 0)
        {
            switch (code)
            {
            case 3:
                return 3;

            default:
                break;
            }
        }
    }
    return 100;
}