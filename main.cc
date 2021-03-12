
#include <iostream>
#include "arbitre.hh"
#include "jeu.hh"
#include "brix.hh"
#include "joueurs/joueur_montecarlo_.hh"
#include "tree/narytree.h"
#include "tree/arbrecontigu.h"

int main()
{
    std::srand(std::time(nullptr));

    Joueur_MonteCarlo_ j("test",true);
    for (size_t i = 0;i<10000;++i) {
        j.montecarlo();
    }
    std::cout<<"pass"<<std::endl;
    j.savetree();
    // création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
    Arbitre a (player::M_1,player::RAND2,100);
    // commence le challenge
    int r= a.challenge();
   return r;

}
