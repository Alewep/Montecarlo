#include "arbrebin.h"



Binarytree::Node::Node(int val,Brix coup) : _val(val),_coup(coup),_right(nullptr),_left(nullptr) {}


void Binarytree::Node::setVal(int val)
{
    _val = val;
}

int Binarytree::Node::getVal()
{
    return _val;
}


Binarytree::Node &Binarytree::Node::getRight()
{
    if (rightIsNull()) _right = new Node(0,Brix ());
    return *_right;
}

Binarytree::Node &Binarytree::Node::getLeft()
{
    if (leftIsNull()) _left = new Node(0,Brix ());
    return *_left;
}

Brix &Binarytree::Node::getCoup()
{
    return _coup;
}

bool Binarytree::Node::rightIsNull()
{
    return (_right == nullptr);
}

bool Binarytree::Node::leftIsNull()
{
    return (_left == nullptr);
}

Binarytree::Binarytree()
{
    _root = nullptr;
}

Binarytree::Binarytree(int val,Brix coup)
{
    _root = new Node (val,coup);
}

Binarytree::~Binarytree()
{
    if (!isnull()) {
        std::queue<Node *> q;
        q.push(_root);
        while(!q.empty())
        {
            Node *node = q.front();
            q.pop();
            if (!node->leftIsNull())
                q.push(&node->getLeft());
            if (!node->rightIsNull())
                q.push(&node->getRight());
            delete node;

        }

    }
}

Binarytree::Node &Binarytree::getNode()
{
    if (isnull()) _root = new Node(0,Brix());
    return *_root;
}

bool Binarytree::isnull() const
{
    return (_root == nullptr);
}
