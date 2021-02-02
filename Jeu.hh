#pragma once 
#include <vector>
using coup = int;
using etat = std::vector<std::vector<int>>;
class Jeu {
private:
    etat _e;
public:
    int gagner () ; // -1:l'universelle ,1 = l'existensielle, 0:aucune victoire
    coup coupleplusgrand (); 
    virtual std::vector<etat> getallposibilities(); 
    //ordre sur les coup : le plus en haut à gauche = le plus petit;
    // le plus en bas à droite : le plus grand
    virtual void play(coup c);
};

/*
class Morpion : public Jeu {
public:
    Morpion (unsigned int longueur, unsigned int largeur);
    int gagner() override;
    coup coupleplusgrand() override;
    std::vector<etat> getallposibilities() override;
    void play(coup c) override;

};*/