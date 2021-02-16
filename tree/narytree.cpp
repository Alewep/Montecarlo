#include "narytree.h"

Narytree::Node::Node(int val) : _val(val),_father(nullptr) {}

Narytree::Node::Node(int val, Node &father) : _val(val),_father(&father) {}

bool Narytree::Node::isaleaf() const
{
    return _sons.empty();
}

bool Narytree::Node::havefather() const
{
    return _father != nullptr;
}

int Narytree::Node::getVal()
{
    return _val;
}

Narytree::Node &Narytree::Node::getNode(size_t i)
{
    return *_sons.at(i);
}

size_t Narytree::Node::numberOfsons()
{
    return _sons.size();
}

Narytree::Node &Narytree::Node::getFather()
{
    if(!havefather()) _father = new Node (0);
    return *_father;
}

void Narytree::Node::addNode(int val)
{
    _sons.push_back(new Node(val));

}





Narytree::Narytree(int val) :_root ( new Node(val)) {}


Narytree::~Narytree()
{
    if (!isnull()) {
        std::queue<Node *> q;
        q.push(_root);
        _root = nullptr;
        while (!q.empty()) {
            Node *node = q.front();
            q.pop();
            if(!node->isaleaf()) {
                for(size_t i = 0;i<node->numberOfsons();++i)
                {
                    q.push(&node->getNode(i));
                }
            }
            delete node;

        }
    }
}

Narytree::Node &Narytree::getNode()
{
    if(isnull()) _root = new Node (0);
    return *_root;
}

bool Narytree::isnull()
{
    return _root == nullptr;
}
