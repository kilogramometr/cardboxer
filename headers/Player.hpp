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
    sf::Texture blockTexture;
    sf::Texture hurtTexture;

    Shield* shield;

    int frame;
    int maxFrame;
    int animationTimer;
    int animationType;

    bool *animationEnd = nullptr;

    std::list<Card *> discardPile;

    void initSprite();
    void onDraw(sf::RenderTarget &target, sf::Transform& transform);
    void animate();
    void setFrame();
    void onUpdate(sf::Vector2f mousePos);
    
    void setAttack1();
    void setAttack2();
    void setAttack3();
    void setDead();
    void setBlock();
    void setHurt();
    void setIdle();
public:
    Player();

    std::list<Card *> hand;
    void draw(); // from deck to hand
    void discard(Card *card); // from hand to discard
    void shuffle(); // shuffle order in deck
    void reshuffle(); // discardPile -> deck + shuffle

    //Animations
    void attack1();
    void attack2();
    void attack3();
    void dead();
    void dead(bool *animationEnd);
    void block();
    void hurt();
    void burnCard(Card *card);
    int getDiscardSize();
    bool handEmpty();
};
