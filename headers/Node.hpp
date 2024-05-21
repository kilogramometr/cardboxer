#pragma once
#include <list>

class Node
{
    public:
        std::list<Node*> children;
        Node();
};