#include "Button.h"


void Button::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
}

void Button::initShape(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	this->shape.setPosition(position);
	this->shape.setSize(size);
	this->shape.setFillColor(color);
}

void Button::initText(sf::Vector2f position, sf::Vector2f textOffset, int textSize, sf::String buttonText)
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(textSize);
	this->text.setFillColor(sf::Color::White);
	this->text.setString(buttonText);
	this->text.setPosition(position);
	this->text.move(textOffset);
}

Button::Button()
{

}

void Button::initButton(sf::Vector2f position, sf::Vector2f size, sf::Vector2f textOffset, int textSize, sf::Color color, sf::String buttonText)
{
	this->initShape(position, size, color);
	this->initFont();
	this->initText(position, textOffset, textSize, buttonText);
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

sf::FloatRect Button::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}
