#pragma once


#include "joueur.h"
#include "Jeu.hh"


class Joueur_MonteCarlo_ : public Joueur
{
public:
  Joueur_MonteCarlo_(std::string nom, bool joueur);
  char nom_abbrege() const override;

  void recherche_coup(Jeu jeu, int & coup) override;
};
