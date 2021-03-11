#ifndef NARYTREE_H
#define NARYTREE_H
#include <vector>
#include "arbrebin.h"
#include "arbrecontigu.h"
#include <queue>
class Narytree
{

public:
    class Node
    {
    private:
        int _val;
        int _iterations;
        Brix _coup;
        Node  *_father;
        std::vector<Node *> _sons;
    public:
        Node(int val,int iterations, Brix const& coup);
        Node (int val,int iterations, Brix const& coup,Node &father);
        Node(Node const& node) = delete;
        ~Node() {}
        bool isaleaf() const;
        bool havefather() const ;
        int getVal() const;
        int getIterations () const;
        Brix getCoup() const ;
        void setVal( int val);
        void setCoup(Brix coup);
        void setIterations(int iterations);
        void setFather (Node &father);
        Node &get();
        const Node &getConst() const;
        void set(int val,int iterations,Brix coup);
        Node &getNode (size_t i);
        const Node &getNodeConst (size_t i) const;
        size_t numberOfsons () const ;
        Node &getFather();
        const Node& getFatherConst() const;
        void addNode(int val, int iterations,Brix coup);
        void addNode (int val,int iterations,Brix coup,Node &father);



    };

private:
      Node *_root;
public:
    Narytree();
    Narytree(int val,int iterations, Brix coup);
    Narytree(Narytree const& n) = delete;
    Narytree(Binarytree const& bin); // à définir
    ~Narytree();
    Node &getNode();
    const Node &getNodeConst() const;
    void setNode(int val,int iterations, Brix coup);
    bool isnull() const;
    void prefixe() const;
    void toCsv (std::string filename) const;
    size_t numberofnodes ();
};

#endif // NARYTREE_H
