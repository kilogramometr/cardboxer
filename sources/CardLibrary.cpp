#include "../headers/CardLibrary.hpp"

#include <iostream>

CardLibrary::CardLibrary(std::list<Card *> *library)
{
    this->library = library;

    this->it = this->library->begin();
    this->card = **(this->it);
    this->cardNext = (this->it == --this->library->end()) ? **(this->library->begin()) : **(++this->it);
    this->cardPrev = **(--this->library->end());

    // std::cerr<<this->card.getName()<<std::endl;
    // std::cerr<<this->cardNext.getName()<<std::endl;
    // std::cerr<<this->cardPrev.getName()<<std::endl;

    this->updateCards();
    this->showCards();

    this->returnButton = new Button(sf::Vector2f(300, 0), sf::Vector2f(200, 50), sf::Vector2f(55, 0), 40, sf::Color::Red, "Return", 3);
    this->nextButton = new Button({760, 250}, {40, 100}, {7, 15}, 40, sf::Color(50, 50, 50), "->", 1);
    this->prevButton = new Button({0, 250}, {40, 100}, {7, 15}, 40, sf::Color(50, 50, 50), "<-", 2);
    
    this->appendChild(this->returnButton);
    this->appendChild(this->nextButton);
    this->appendChild(this->prevButton);

}

void CardLibrary::onDraw(sf::RenderTarget &target){}

/* internal utility */

void CardLibrary::next() 
{
    this->cardPrev = this->card;
    this->card = this->cardNext;

    if (this->it == --this->library->end())
        this->it = this->library->begin();
    else
        ++this->it;

    this->cardNext = **(this->it);
}

void CardLibrary::prev() 
{
    this->cardNext = this->card;
    this->card = this->cardPrev;
    
    if (this->it == this->library->begin())
        this->it = --this->library->end();
    else
        --this->it;
    
    auto tempIt = this->it;
    for (int i = 0; i < 2; i++)
    {
        if (tempIt == this->library->begin())
            tempIt =--this->library->end();
        else
            --tempIt;
    }

    this->cardPrev = **(tempIt);

}

void CardLibrary::hideCards()
{
    this->removeChild(&this->card);
    this->removeChild(&this->cardNext);
    this->removeChild(&this->cardPrev);
}

void CardLibrary::showCards()
{
    this->appendChild(&this->card);
    this->appendChild(&this->cardNext);
    this->appendChild(&this->cardPrev);
}

void CardLibrary::updateCards()
{
    this->card.setScale({1.0, 1.0});
    this->card.setPosition({275, 125});

    this->cardNext.setScale({0.5, 0.5});
    this->cardNext.setPosition({600, 212.5});
    
    this->cardPrev.setScale({0.5, 0.5});
    this->cardPrev.setPosition({75, 212.5});
    
}

/* internal handling of button clicks */

int CardLibrary::onButtonClick(sf::Vector2f mousePos)
{
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        int code = (*i)->buttonClick(mousePos);
        if (code != 0)
        {
            switch(code)
            {
            case 1:
                this->hideCards();
                this->next();
                this->updateCards();
                this->showCards();
                return 100;

            case 2:
                this->hideCards();
                this->prev();
                this->showCards();
                this->updateCards();
                return 100;

            case 3:
                return 3;

            default:
                break;
            }
        }
    }
    return 100;
}