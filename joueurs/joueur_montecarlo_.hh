#pragma once

#include <stdlib.h>
#include <time.h>
#include "joueur.hh"
#include "narytree.h"
#include "arbrecontigu.h"
#include "../arbitre.hh"
#include <fstream>
#include <math.h>
#include <stack>
#include <float.h>

class Joueur_MonteCarlo_ : public Joueur
{
private:
    Narytree _tree;
    Narytree::Node * _courant;
    int tour;

public:
    const static double PONDERATION;
    Joueur_MonteCarlo_(std::string nom, bool joueur);
    void savetree();

    //char nom_abbrege() const override;
    void recherche_coup(Jeu j, Brix & coup) override;
    static bool egalBrix (Brix a, Brix b);
    static Brix getBrixJouer(const Jeu &fils, const Jeu &pere);
    static double uperboundconfidence(Narytree::Node& node); // calcule l'uperboundconfidence d'un noeud
    static Jeu etat (const Narytree::Node& node); // renvoie le plateau du jeux correspondant au noeud
    static std::vector<Brix> coupspossible(Jeu jeu); //renvoie un vecteur contenant tout les coups possbile
    static bool coupvisite(Brix b,Narytree::Node& node );
    static std::vector<Brix> coupsnonvisites (Narytree::Node& node ); //renvoie le vecteur contenant les coups qui n'ont pas été visité
    static Narytree::Node& maxUBC(Narytree::Node& node); // renvoie parmi les fils du noeud appelé celui qui maximise UBC

    size_t minimisation ();
    size_t maximsation ();

    static Narytree::Node& descent (Narytree::Node& node); // s'arrête sur un noeud d'ont un fils n'a pas encore été exploré
    static Narytree::Node& growth(Narytree::Node& node ); // creer un nouveau noeud parmis les succeur de l'etat etiquetant la feuille
    static int rollout( Narytree::Node& node); //fait une partie au hasard à partir d'un noeud, renvoie la valuation de cette partie
    static void update(Narytree::Node& node,int val); // met à jour la branche complete jusqu'au pere
    void montecarlo();

};
