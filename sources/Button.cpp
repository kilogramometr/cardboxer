#include "../headers/Button.hpp"

Button::Button(std::string text="Button", sf::Vector2f size={10,10}, int fontSize=18, std::string fontPath="./res/fonts/ARIAL.ttf") 
{
    this->text = new sf::Text();
    this->setFont(fontPath);
    this->setText(text);
    this->setFontSize(fontSize);
    this->setSize(size);
    this->setFillColor(sf::Color::Green);
}

void Button::setFont(std::string fontPath)
/* Load font from fontPath and set it as current font */
{
    this->font = new sf::Font();
    this->font->loadFromFile(fontPath);
    this->text->setFont(*this->font);
}

void Button::setText(std::string text)
/* Set new button text */
{
    this->text->setString(text);
}

void Button::resetText()
/* reset button text to default */
{
    this->text->setString("Button");
}

void Button::setFontSize(int size)
{
    this->text->setCharacterSize(size);
}

void Button::onDraw(sf::RenderTarget& target)
{
    target.draw(*this);
    target.draw(*this->text);
}