#include "../headers/Node.hpp"
#include <iostream>

Node::Node() {}
// Node::~Node() {}
void Node::appendChild(Node* child) { this->children.emplace_back(child); }

void Node::removeChild(Node* child) 
/* remove that emelement from list  */
{
    this->children.remove(child);
}

void Node::draw(sf::RenderTarget& target, sf::Transform& parentTransform)
/* draw self and children */
{
    // combine the parent transform with the node's one
    sf::Transform combinedTransform = parentTransform * this->transform;

    // let the node draw itself
    onDraw(target, combinedTransform);

    // draw its children
    for (auto it = this->children.begin(); it != this->children.end(); ++it)
    {
        // std::cerr<<*it<<"\n";
        if (*it != nullptr)
            (*it)->draw(target, combinedTransform);
    }
}

int Node::buttonClick(sf::Vector2f mousePosition)
/* check click for self and children*/
{
    int code = this->onButtonClick(mousePosition);
    if(code != 0)
    {
        // std::cerr<<"great success!\n";  
        return code;
    }
    else
    {    
        // std::cerr<<"I am checking my children\n";
        for (auto it = this->children.begin(); it != this->children.end(); ++it)
        {
            // std::cerr<<"I am checking: "<<*it<<"\n";
            code = (*it)->buttonClick(mousePosition);
            if(code != 0)
                return code;       
        }
    }
    
    return 0;
}

void Node::update(sf::Vector2f mousePos)
{
    this->onUpdate(mousePos);

    for (auto it = this->children.begin(); it != this->children.end(); ++it)
    {
        (*it)->update(mousePos);
    }
}

void Node::hide() { this->hidden = false; }
void Node::reveal() { this->hidden = true; }
