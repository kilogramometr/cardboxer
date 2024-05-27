#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Button : public Node, public sf::RectangleShape
{
    sf::Font *font;
    sf::Text *text;

    void onDraw(sf::RenderTarget& target) override;

    void setText(sf::Vector2f position, std::string buttonText, int textSize, sf::Vector2f textOffset);
    void setFont();
public:
    //Button(std::string text, sf::Vector2f size, int fontSize, std::string fontPath);
    Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f textOffset, int textSize, sf::Color color, std::string buttonText);
    
    
    void resetText();

};

