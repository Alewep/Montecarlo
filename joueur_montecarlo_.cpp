#include "joueur_montecarlo_.h"


Joueur_MonteCarolo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}



char Joueur_MonteCarlo_::nom_abbrege() const
{
    return 'M';
}

void Joueur_MonteCarlo_::recherche_coup(Jeu jeu, int &coup)
{

}
