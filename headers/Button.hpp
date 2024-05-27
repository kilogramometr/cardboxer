#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Button : public Node, public sf::RectangleShape
{
    sf::Font *font;
    sf::Text *text;

    void onDraw(sf::RenderTarget& target) override;

public:
    Button(std::string text, sf::Vector2f size, int fontSize, std::string fontPath);
    void setText(std::string text);
    void setFont(std::string fontPath);
    void setFontSize(int size);
    void resetText();

};

