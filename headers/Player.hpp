#include "Boxer.hpp"
#include "Shield.hpp"

class Player : public Boxer
{
private:
    sf::Sprite sprite;

    sf::Texture idleTexture;
    sf::Texture attack1Texture;
    sf::Texture attack2Texture;
    sf::Texture attack3Texture;
    sf::Texture deadTexture;

    Shield* shield;

    int frame;
    int maxFrame;
    int animationTimer;
    int animationType;

    std::list<Card *> *hand;
    std::list<Card *> *discardPile;

    void initSprite();
    void onDraw(sf::RenderTarget &target, sf::Transform& transform);
    void animate();
    void setFrame();
    void onUpdate();

    void setAttack1();
    void setIdle();
public:
    Player();

    void draw(); // from deck to hand
    void discard(); // from hand to discard
    void shuffle(); // shuffle order in deck
    void reshuffle(); // discardPile -> deck + shuffle

};
