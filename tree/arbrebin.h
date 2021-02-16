#ifndef ARBRE_H
#define ARBRE_H
#include <vector>
#include "queue"
#include "../brix.hh"
class Narytree;
class ArbreContigu;

class Binarytree  {
private:
    //définition avec une classe interne
    class Node {
    private:
        int _val;
        Brix _coup;
        Node *_right,*_left;
    public:

        Node(Node const& node) =delete;
        ~Node () {}
        Node(int val,Brix coup);
        void setVal(int val);
        int getVal();
        Node& getRight();
        Node& getLeft();
        Brix& getCoup ();
        bool rightIsNull();
        bool leftIsNull();
    };

    Node *_root;
public:
    Binarytree();
    Binarytree(ArbreContigu const& a); // à définir
    Binarytree(Narytree const& n ); // à définir
    Binarytree(int val,Brix coup);
    Binarytree(Binarytree const& t) = delete;
    ~Binarytree();

    Node& getNode();
    bool isnull() const;
    void prefixe () const; // à definir lecture du l'arbre celon l'ordre prefixe (sans recursivité)
};




#endif // ARBRE_H
