#ifndef NARYTREE_H
#define NARYTREE_H
#include <vector>
#include "arbrebin.h"
#include <queue>
class Narytree
{
private:
public:
    class Node
    {
    private:
        int _val;
        Brix _coup;
        Node  *_father;
        std::vector<Node *> _sons;
    public:
        Node(int val,Brix const& coup);
        Node (int val,Brix const& coup,Node &father);
        Node(Node const& node) = delete;
        ~Node() {}
        bool isaleaf() const;
        bool havefather() const ;
        int getVal() const;
        Brix getCoup() const ;
        void setVal();
        void setCoup();
        
        Node &getNode (size_t i);
        size_t numberOfsons () const ;
        Node &getFather() ;
        void addNode(int val, Brix coup);

        int getVal();
    };

    Node *_root;
public:
    Narytree();
    Narytree(int val, Brix coup);
    Narytree(Narytree const& n) = delete;
    Narytree(Binarytree const& bin); // à définir
    ~Narytree();
    Node &getNode();
    bool isnull();

};

#endif // NARYTREE_H
