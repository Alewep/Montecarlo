
#include <iostream>
#include "arbitre.hh"
#include "jeu.hh"
#include "brix.hh"
#include "tree/narytree.h"
#include "tree/arbrecontigu.h"

int main()
{
    Narytree n1(1,0,Brix(0,0,0,0));
    n1.getNode().addNode(2,0,Brix(0,0,0,0));
    n1.getNode().addNode(3,0,Brix(0,0,0,0));
    n1.getNode().addNode(4,0,Brix(0,0,0,0));

    n1.getNode().getNode(0).addNode(5,0,Brix(0,0,0,0));
    n1.getNode().getNode(1).addNode(6,0,Brix(0,0,0,0));
    n1.getNode().getNode(1).addNode(7,0,Brix(0,0,0,0));
    n1.prefixe();
    Binarytree b1(1,0,Brix(0,0,0,0));
    b1.getNode().setLeft(2,0,Brix(0,0,0,0));
    b1.getNode().getLeft().setRight(3,0,Brix(0,0,0,0));

    b1.getNode().getLeft().setLeft(4,0,Brix(0,0,0,0));
    b1.getNode().getLeft().getLeft().setRight(5,0,Brix(0,0,0,0));

    b1.prefixe();

    Narytree n(b1);
    n.prefixe();

//std::cout<<c2.values.size()<<std::endl;

//    //initialise la graine du générateur aléatoire
//    std::srand(std::time(nullptr));

//    // création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
//    Arbitre a (player::RAND,player::RAND2,10);
//    // commence le challenge
//    int r= a.challenge();
//   return r;

}
