#include "../headers/Button.hpp"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f textOffset, int textSize, sf::Color color, std::string buttonText) 
{
    this->setPosition(position);
    this->setSize(size);
    this->setFillColor(color);

    this->setFont();
    this->setText(position, buttonText, textSize, textOffset);
}

void Button::setFont()
{
    this->font = new sf::Font();
    this->font->loadFromFile("./res/fonts/Dosis-Light.ttf");
}

void Button::setText(sf::Vector2f position, std::string buttonText, int textSize, sf::Vector2f textOffset)
{
    this->text = new sf::Text();
    this->text->setFont(*this->font);
    this->text->setCharacterSize(textSize);
    this->text->setFillColor(sf::Color::White);
    this->text->setString(buttonText);
    this->text->setPosition(position);
    this->text->move(textOffset);
}

void Button::resetText()
{
    this->text->setString("Button");
}

void Button::onDraw(sf::RenderTarget& target)
{
    target.draw(*this);
    target.draw(*this->text);
}