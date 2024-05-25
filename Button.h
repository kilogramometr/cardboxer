#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Button
{
private:
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	void initFont();
	void initShape(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	void initText(sf::Vector2f position, sf::Vector2f textOffset, int textSize, sf::String buttonText);

public:
	Button();
	void initButton(sf::Vector2f position, sf::Vector2f size, sf::Vector2f textOffset, int textSize, sf::Color color, sf::String buttonText);
	void render(sf::RenderTarget& target);
	sf::FloatRect getGlobalBounds();
};
