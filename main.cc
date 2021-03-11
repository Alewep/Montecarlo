
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
    Joueur_MonteCarlo_ j("Alex",true);
    size_t i = 0;
    while (i< 10000)
    {
      j.montecarlo();
      ++i;
    }
    std::cout<<"montecarlo...succes !"<<std::endl;
    j.savetree();







//    // création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
//    Arbitre a (player::RAND,player::RAND2,10);
//    // commence le challenge
//    int r= a.challenge();
//   return r;

}
