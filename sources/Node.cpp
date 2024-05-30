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
            return;
            // std::cout<<"Great Success!\n";
        }
    }
}

void Node::draw(sf::RenderTarget& target)
/* draw self and children */
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

int Node::buttonClick(sf::Vector2f mousePosition)
/* check click for self and children*/
{
    int code = this->onButtonClick(mousePosition);
    if(code != 0)
    {
        std::cerr<<"great success!\n";  
        return code;
    }
    else
    {    
        std::cerr<<"I am checking my children\n";
        for (auto it = this->children.begin(); it != this->children.end(); ++it)
        {
            std::cerr<<"I am checking: "<<*it<<"\n";
            code = (*it)->buttonClick(mousePosition);
            if(code != 0)
                return code;       
        }
    }
    
    return 0;
}

void Node::hide() { this->hidden = false; }
void Node::reveal() { this->hidden = true; }
