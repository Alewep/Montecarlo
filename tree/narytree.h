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
        Node(int val,);
        Node (int val,Brix coup,Node &father);
        Node(Node const& node) = delete;
        ~Node() {}
        bool isaleaf() const;
        bool havefather() const ;
        int getVal();
        Node &getNode (size_t i);
        size_t numberOfsons ();
        Node &getFather();
        void addNode(int val);

    };

    Node *_root;
public:
    Narytree();
    Narytree(int val);
    Narytree(Narytree const& n) = delete;
    Narytree(Binarytree const& bin); // à définir
    ~Narytree();
    Node &getNode();
    bool isnull();

};

#endif // NARYTREE_H
