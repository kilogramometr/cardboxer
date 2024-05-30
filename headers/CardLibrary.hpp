#pragma once
#include "Node.hpp"
#include "Button.hpp"

class CardLibrary : public Node
{
private:
    Button *returnButton;

    void onDraw(sf::RenderTarget &target);

public:
    CardLibrary();
};