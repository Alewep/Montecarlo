#include "narytree.h"



Narytree::Node::Node(int val, int iterations, const Brix &coup) : _val(val),_iterations(iterations),_coup(coup),_father(nullptr) {}

Narytree::Node::Node(int val, int iterations, const Brix &coup, Narytree::Node &father)  : _val(val),_iterations(iterations),_coup(coup),_father(&father) {}



bool Narytree::Node::isaleaf() const
{
    return _sons.empty();
}

bool Narytree::Node::havefather() const
{
    return _father != nullptr;
}

int Narytree::Node::getVal() const
{
    return _val;
}


int Narytree::Node::getIterations() const
{
    return _iterations;
}

Brix Narytree::Node::getCoup() const
{
    return _coup;
}

void Narytree::Node::setVal(int val)
{
    _val = val;
}

void Narytree::Node::setCoup(Brix coup)
{
    _coup = coup;
}

void Narytree::Node::setIterations(int iterations)
{
    _iterations = iterations;
}

void Narytree::Node::setFather(Narytree::Node &father)
{
    _father = &father;
}

Narytree::Node &Narytree::Node::get()
{
    return *this;
}

const Narytree::Node &Narytree::Node::getConst() const
{
    return *this;
}

void Narytree::Node::set(int val, int iterations, Brix coup)
{
    _val = val;
    _iterations = iterations;
    _coup = coup;
}

Narytree::Node &Narytree::Node::getNode(size_t i)
{
    return *_sons.at(i);
}

const Narytree::Node &Narytree::Node::getNodeConst(size_t i) const
{
    return *_sons.at(i);
}

size_t Narytree::Node::numberOfsons() const
{
    return _sons.size();
}

Narytree::Node &Narytree::Node::getFather()
{
    if(!havefather()) _father = new Node (0,0,Brix());
    return *_father;
}

const Narytree::Node &Narytree::Node::getFatherConst() const
{
    return *_father;
}

void Narytree::Node::addNode(int val,int iterations, Brix coup)
{
    _sons.push_back(new Node(val,iterations,coup,*this));

}

void Narytree::Node::addNode(int val, int iterations, Brix coup, Narytree::Node &father)
{
    _sons.push_back(new Node(val,iterations,coup,father));
}

size_t Narytree::numberofnodes()
{
    size_t numberofnodes = 0;
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
            ++numberofnodes;

        }
    }
    return numberofnodes;
}





Narytree::Narytree()
{
    _root = nullptr;
}

Narytree::Narytree(Binarytree const &bin)
{

    if(!bin.isnull()) {
        std::queue< const Binarytree::Node *> qb;
        std::queue<Node *> qn;
        qb.push(&bin.getNodeConst());
        _root = new Node(bin.getNodeConst().getVal(),bin.getNodeConst().getIterations(),bin.getNodeConst().getCoup());
        qn.push(_root);
        while(!qb.empty()) {
            const Binarytree::Node * nb = qb.front();
            qb.pop();
            Node *nn = qn.front();
            qn.pop();
            if(!nb->leftIsNull()) {
                qb.push(&nb->getLeftConst());
                nn->addNode(nb->getLeftConst().getVal(),nb->getIterations(),nb->getLeftConst().getCoup(),*nn);
                qn.push(&nn->getNode(0));
            }
            if(!nb->rightIsNull()) {
                qb.push(&nb->getRightConst());
                nn->getFather().addNode(nb->getRightConst().getVal(),nb->getRightConst().getIterations(),nb->getRightConst().getCoup(),nn->getFather());
                qn.push(&nn->getFather().getNode(nn->getFather().numberOfsons()-1));
            }

        }
    }

}

Narytree::Narytree(int val,int iterations, Brix coup ) :_root ( new Node(val,iterations, coup ) ) {}


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
    //if(isnull()) _root = new Node (0,0,Brix());
    return *_root;
}

const Narytree::Node &Narytree::getNodeConst() const
{
    return *_root;
}

void Narytree::setNode(int val, int iterations, Brix coup)
{
    _root->setVal(val);
    _root->setIterations(iterations);
    _root->setCoup(coup);

}

bool Narytree::isnull() const
{
    return _root == nullptr;
}

void Narytree::prefixe() const
{
    if (!isnull()) {
        std::queue<Node *> q;
        q.push(_root);
        while (!q.empty()) {
            Node *node = q.front();
            q.pop();
            if(!node->isaleaf()) {
                for(size_t i = 0;i<node->numberOfsons();++i)
                {
                    q.push(&node->getNode(i));
                }
            }
            if (node->havefather())
                std::cout<<node->getFather().getVal()<<"f";
            std::cout<<node->getVal()<<std::endl;
        }
    }
}

void Narytree::toCsv(std::string filename) const
{
    ArbreContigu c (*this);
    c.to_csv(filename);
}


