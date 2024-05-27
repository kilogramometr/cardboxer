#include "../headers/Node.hpp"
#include <iostream>

Node::Node() {}
// Node::~Node() {}
void Node::appendChild(Node* child) { this->children.emplace_back(child); }

void Node::removeChild(Node* child) 
/* remove that emelement from list  */
{
    for (auto it = this->children.begin(); it != this->children.end(); ++it)
    {
        if (*it == child)
        {
            this->children.erase(it);
            std::cout<<"Great Success!\n";
        }
    }
}

void Node::draw(sf::RenderTarget& target)
{
    // combine the parent transform with the node's one

    // let the node draw itself
    onDraw(target);

    // draw its children
    for (auto it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->draw(target);
    }
}


void Node::buttonClick(sf::Vector2f mousePosition)
{
    this->onButtonClick(mousePosition);

    for (auto it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->buttonClick(mousePosition);
    }
}