#pragma once
#include "Node.hpp"
#include "Button.hpp"
#include "Card.hpp" 

class CardLibrary : public Node
{
private:
    Button *returnButton;
    Button *nextButton;
    Button *prevButton;
    // pointer to library of cards
    std::list<Card *> *library;
    // iterator to next card
    std::list<Card *>::iterator it; 
    // current shown card
    Card card;
    // next shown card
    Card cardNext;
    // previously shown card
    Card cardPrev;
    
    void onDraw(sf::RenderTarget &target);
    int onButtonClick(sf::Vector2f mousePos);

    void updateCards();
    void hideCards();
    void showCards();
    void next();
    void prev();

public:
    CardLibrary(std::list<Card *> *library);

    
};