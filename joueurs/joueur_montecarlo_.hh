#pragma once

#include "joueur.hh"
#include "narytree.h"
#include "arbrecontigu.h"
#include "../arbitre.hh"
#include <fstream>
#include <math.h>
#include <float.h>
#include <limits>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class Joueur_MonteCarlo_ : public Joueur
{
private:
    static Narytree _tree;
    Narytree::Node * _courant;
    int tour;

public:
    const static double PONDERATION;
    Joueur_MonteCarlo_(std::string nom, bool joueur);
    void static savetree();

    //char nom_abbrege() const override;
    void recherche_coup(Jeu j, Brix & coup) override;
    static bool egalBrix (Brix a, Brix b);
    static Brix getBrixJouer(const Jeu &fils, const Jeu &pere);
    static double uperboundconfidence(Narytree::Node& node); // calcule l'uperboundconfidence d'un noeud
    static Jeu etat (const Narytree::Node& node); // renvoie le plateau du jeux correspondant au noeud
    static std::vector<Brix> coupspossible(Jeu const& jeu); //renvoie un vecteur contenant tout les coups possbile
    static bool coupvisite(Brix b,Narytree::Node& node );
    static std::vector<Brix> coupsnonvisites (Narytree::Node& node,Jeu const& jeu ); //renvoie le vecteur contenant les coups qui n'ont pas été visité
    static int coupPresent (Narytree::Node& node,Brix coup);

    static Narytree::Node& maxUBC(Narytree::Node& node); // renvoie parmi les fils du noeud appelé celui qui maximise UBC

    Narytree::Node& minimisation (Jeu const& jeu);
    Narytree::Node& maximsation (Jeu const& jeu);


    static Narytree::Node& descent (Narytree::Node& node); // s'arrête sur un noeud d'ont un fils n'a pas encore été exploré
    static Narytree::Node& growth(Narytree::Node& node ); // creer un nouveau noeud parmis les succeur de l'etat etiquetant la feuille
    static int rollout( Narytree::Node& node); //fait une partie au hasard à partir d'un noeud, renvoie la valuation de cette partie
    static void update(Narytree::Node& node,int val); // met à jour la branche complete jusqu'au pere
    static void update(Narytree::Node& node,int val,Narytree::Node& father);
    void montecarlo();
    void montecarlo_sans_update();

    // stratigies
    static bool strategieTroisalignement(Brix coup,Jeu const& jeu,bool joueur);
    static Brix strategieDirectwinContre (Jeu const& jeu,bool joueur);
    static void elagage (Narytree::Node& node,Jeu const& jeu, bool joueur, duration<double, std::milli> temp);

};

