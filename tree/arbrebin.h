#ifndef ARBRE_H
#define ARBRE_H
#include <vector>
#include "queue"
#include "../brix.hh"
class Narytree;
class ArbreContigu;

class Binarytree  {
public :
    //définition avec une classe interne
    class Node {
    private:
        int _val;
        int _iterations;
        Brix _coup;

        Node *_right,*_left;
    public:

        Node(Node const& node) =delete;
        ~Node () {}
        Node(int val,int iterations,Brix coup);
        void setVal(int val);
        int getVal() const;
        void setLeft(int val,int iterations,Brix coup);
        void setRight(int val,int iterations,Brix coup);
        Node& getRight();
        Node& getLeft();
        const Node &getRightConst() const;
        const Node &getLeftConst() const;
        const Node &get() const;
        Node &get();
        void set (int val, int iterations,Brix coup);

        Brix getCoup () const;
        bool rightIsNull() const ;
        bool leftIsNull() const;
        int getIterations() const;
        void setIterations(int iterations);
    };
private:
    Node *_root;
public:
    Binarytree();
    Binarytree(ArbreContigu const& a); // à définir
    Binarytree(Narytree const& n ); // à définir
    Binarytree(int val,int iterations,Brix coup);
    Binarytree(Binarytree const& t) = delete;
    ~Binarytree();
    Node& getNode();
    const Node &getNodeConst() const;
    bool isnull() const;
    void prefixe () const; // à definir lecture du l'arbre celon l'ordre prefixe (sans recursivité)
    size_t numberofnodes() const;
};




#endif // ARBRE_H
