#include "arbrebin.h"
#include "arbrecontigu.h"
#include "narytree.h"

int Binarytree::Node::getIterations() const
{
    return _iterations;
}

void Binarytree::Node::setIterations(int iterations)
{
    _iterations = iterations;
}

Binarytree::Node::Node(int val,int iterations,Brix coup) : _val(val),_iterations(iterations),_coup(coup),_right(nullptr),_left(nullptr) {}


void Binarytree::Node::setVal(int val)
{
    _val = val;
}

int Binarytree::Node::getVal() const
{
    return _val;
}

void Binarytree::Node::setLeft(int val, int iterations, Brix coup)
{
    _left = new Node(val,iterations,coup);
}

void Binarytree::Node::setRight(int val, int iterations, Brix coup)
{
    _right = new Node(val,iterations,coup);
}


Binarytree::Node &Binarytree::Node::getRight()
{
    if (rightIsNull()) _right = new Node(0,0,Brix(0,0,0,0));
    return *_right;
}

Binarytree::Node &Binarytree::Node::getLeft()
{
    if (leftIsNull()) _left = new Node(0,0,Brix(0,0,0,0));
    return *_left;
}

const Binarytree::Node &Binarytree::Node::getRightConst() const
{
    return *_right;
}

const Binarytree::Node &Binarytree::Node::getLeftConst() const
{
    return *_left;
}

const Binarytree::Node &Binarytree::Node::get() const
{
    return *this;
}

Binarytree::Node &Binarytree::Node::get()
{
    return *this;
}

void Binarytree::Node::set(int val, int iterations, Brix coup)
{
    _val = val;
    _iterations = iterations;
    _coup = coup;
}

Brix Binarytree::Node::getCoup() const
{
    return _coup;
}



bool Binarytree::Node::rightIsNull() const
{
    return (_right == nullptr);
}

bool Binarytree::Node::leftIsNull() const
{
    return (_left == nullptr);
}


Binarytree::Binarytree()
{
    _root = nullptr;
}

Binarytree::Binarytree(const ArbreContigu &a)
{
    std::vector<element> values(a.getvalues());
    if(values.size()>0) {
        std::queue<Node *> q;
        std::queue<std::size_t> qi;
        _root = new Node(values[0].value,values[0].iterations, values[0].brix);
        q.push(_root);
        qi.push(0);
        while(!q.empty())
        {
            Node *node = q.front();
            std::size_t i = qi.front();
            q.pop();
            qi.pop();
            std::cout<<values[(i+1)*2-1].isnull<<std::endl;
            if(!values[(i+1)*2-1].isnull && (i+1)*2-1 < values.size()) {

                node->setLeft(values[(i+1)*2-1].value,values[(i+1)*2-1].iterations, values[(i+1)*2-1].brix);
                q.push(&node->getLeft());
                qi.push((i+1)*2-1);
            }
            std::cout<<values[(i+1)*2].isnull<<"i"<<std::endl;
            if((i+1)*2 < values.size() && !values[(i+1)*2].isnull) {
                node->setRight(values[(i+1)*2].value,values[(i+1)*2].iterations, values[(i+1)*2].brix);
                q.push(&node->getRight());
                qi.push((i+1)*2);
            }


        }
    }
}

Binarytree::Binarytree(const Narytree &n)
{
    if(!n.isnull()) {
        _root = new Node(n.getNodeConst().getVal(),n.getNodeConst().getIterations(),n.getNodeConst().getCoup());
        std::queue<const Narytree::Node *> qn;
        std::queue<Node *> qb;
        qb.push(_root);
        qn.push(&n.getNodeConst());
        while(!qn.empty()) {
            const Narytree::Node &nodeN = *qn.front();
            qn.pop();
            Node * nodeB = qb.front();
            qb.pop();

            if ( ! nodeN.isaleaf() ) {
                nodeB->setLeft(nodeN.getNodeConst(0).getVal(),nodeN.getIterations(),nodeN.getNodeConst(0).getCoup());
                for(std::size_t i=1; i<nodeN.numberOfsons(); i++) {

                    nodeB->setRight(nodeN.getNodeConst(i).getVal(),nodeN.getNodeConst(i).getIterations(),nodeN.getNodeConst(i).getCoup());
                    if(!nodeN.getNodeConst(i).isaleaf()) {
                        qb.push(&nodeB->getLeft());
                        qn.push(&nodeN.getNodeConst(i));
                    }
                    nodeB = &nodeB->getRight();
                }
           }

        }
    }
}

Binarytree::Binarytree(int val,int iterations,Brix coup)
{
    _root = new Node (val,iterations,coup);
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
    if (isnull()) _root = new Node(0,0,Brix());
    return *_root;
}

const Binarytree::Node &Binarytree::getNodeConst() const
{
    return *_root;
}

bool Binarytree::isnull() const
{
    return (_root == nullptr);
}

void Binarytree::prefixe() const
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
            std::cout<<node->getVal()<<";";

        }
        std::cout<<std::endl;

    }
}
