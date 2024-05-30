#pragma once
#include <list>
#include <SFML/Graphics.hpp>

class Node
/* Abstract base class for scene management */
{
private:
    sf::Transform transform;
    bool hidden = false;
    
    void hide();
    void reveal();

    virtual void onDraw(sf::RenderTarget& target) {}
    virtual int onButtonClick(sf::Vector2f mousePosition) {return 0;}

public:
    std::list<Node*> children;

    Node();
    ~Node() {}
    void appendChild(Node *child);
    void removeChild(Node *child);
    // void moveChild(int i);
    // void updateChildren();
    
    
    void draw(sf::RenderTarget& target);
    int buttonClick(sf::Vector2f mousePosition);
};