
#include <iostream>
#include "arbitre.hh"
#include "jeu.hh"
#include "brix.hh"
#include "joueurs/joueur_montecarlo_.hh"
#include "tree/narytree.h"
#include "tree/arbrecontigu.h"

int main()
{

// entrainement
//    std::srand(std::time(nullptr));
//    Joueur_MonteCarlo_ j("test",true);
//    for (size_t k = 0;k<10000000;++k) {
//        std::cout<<k<<std::endl;
//        for (size_t i = 0;i<100000;++i) {
//              j.montecarlo();
//        }
//        std::cout<<"break"<<std::endl;
//        j.savetree();
//        std::cout<<"ok"<<std::endl;
//    }



    //création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
    Arbitre a (player::M_1,player::RAND,20);
    // commence le challenge
    int r= a.challenge();



}
