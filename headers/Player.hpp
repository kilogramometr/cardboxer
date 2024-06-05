#include "Boxer.hpp"

class Player : public Boxer
{
private:
    std::list<Card *> *hand;
    std::list<Card *> *discardPile;

public:
    Player();

    void draw(); // from deck to hand
    void discard(); // from hand to discard
    void shuffle(); // shuffle order in deck
    void reshuffle(); // discardPile -> deck + shuffle

};
