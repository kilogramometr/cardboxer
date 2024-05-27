#pragma once
#include <list>
#include <SFML/Graphics.hpp>

class Node
/* Abstract base class for scene management */
{
private:
    sf::Transform transform;
    
    virtual void onDraw(sf::RenderTarget& target) {}


public:
    std::list<Node*> children;

    Node();
    ~Node() {}
    void appendChild(Node *child);
    void removeChild(Node *child);
    // void moveChild(int i);
    // void updateChildren();
    
    void draw(sf::RenderTarget& target);

};