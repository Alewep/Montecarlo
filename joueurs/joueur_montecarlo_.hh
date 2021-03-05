#pragma once


#include "joueur.hh"
#include "narytree.h"
#include <stack>

class Joueur_MonteCarlo_ : public Joueur
{
private:
    Narytree _tree;
    Narytree::Node &_courant;

public:
  Joueur_MonteCarlo_(std::string nom, bool joueur);
  //char nom_abbrege() const override;
   void recherche_coup(Jeu j, Brix & coup) override;
   static Brix getBrixJouer(Jeu fils, Jeu pere);
   static int uperboundconfidence(Narytree::Node& node); // calcule l'uperboundconfidence d'un noeud
   static Jeu etat (Narytree::Node& node); // renvoie le plateau du jeux correspondant au noeud
   static std::vector<Brix> coupspossible(Jeu jeu); //renvoie un vecteur contenant tout les coups possbile
   static std::vector<Brix> coupsnonvisite (Jeu jeu, Narytree::Node& node ); //renvoie le vecteur contenant les coups qui n'ont pas été visité

   static Narytree::Node& descent (Narytree::Node& node); // s'arrête sur un noeud d'ont un fils n'a pas encore été exploré
   static Narytree::Node& growth(Narytree::Node& node ); // creer un nouveau noeud parmis les succeur de l'etat etiquetant la feuille
   static int rollout(Narytree::Node& node); //fait une partie au hasard à partir d'un noeud, renvoie la valuation de cette partie
   static void update(Narytree::Node& node,int val); // met à jour la branche complete jusqu'au pere
   void montecarlo();

};
