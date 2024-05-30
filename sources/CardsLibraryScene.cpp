#include "../headers/CarsdLibraryScene.hpp"

CardsLibraryScene::CardsLibraryScene()
{
    this->returnButton = new Button(sf::Vector2f(300, 0), sf::Vector2f(200, 50), sf::Vector2f(55, 0), 40, sf::Color::Red, "Return", 3);
    this->appendChild(this->returnButton);
}

void CardsLibraryScene::onDraw(sf::RenderTarget &target){}