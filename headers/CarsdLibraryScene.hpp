#pragma once
#include "Node.hpp"
#include "Button.hpp"

class CardsLibraryScene : public Node
{
private:
    Button *returnButton;

    void onDraw(sf::RenderTarget &target);

public:
    CardsLibraryScene();
};