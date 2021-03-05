#include "joueur_montecarlo_.hh"


Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur),_tree(0,0,Brix()),_courant(_tree.getNode())
{

}



/*char Joueur_MonteCarlo_::nom_abbrege() const
{
    return 'M';
}
*/
void Joueur_MonteCarlo_::recherche_coup(Jeu jeu, Brix &coup)
{

}

Brix Joueur_MonteCarlo_::getBrixJouer(Jeu fils, Jeu pere)
{
    for(size_t i=0;i<MAX_LARGEUR;++i){
        for(size_t j=0;j<MAX_HAUTEUR;++j) {
            if((fils.plateau()[j][i] != pere.plateau()[j][i]) && pere.plateau()[j][i] == '0' ) {
                std::cout<<"enter"<<std::endl;
                if(fils.plateau()[j][i] == 'o') {
                    std::cout<<"OO";
                    if (( j > 0 ) && (fils.plateau()[j-1][i] != pere.plateau()[j-1][i]) && (fils.plateau()[j-1][i] == 'x') && pere.plateau()[j-1][i] == '0' )
                        return Brix(static_cast<int>(i),static_cast<int>(j-1),static_cast<int>(i),static_cast<int>(j));

                    if (( j < MAX_HAUTEUR-1 ) && (fils.plateau()[j+1][i] != pere.plateau()[j+1][i]) && (fils.plateau()[j+1][i] == 'x') && pere.plateau()[j+1][i] == '0' )
                        return Brix(static_cast<int>(i),static_cast<int>(j+1),static_cast<int>(i),static_cast<int>(j));

                    if (( i > 0 ) && (fils.plateau()[j][i-1] != pere.plateau()[j][i-1]) && (fils.plateau()[j][i-1] == 'x') && pere.plateau()[j][i-1] == '0' )
                        return Brix(static_cast<int>(i-1),static_cast<int>(j),static_cast<int>(i),static_cast<int>(j));

                    if (( i < MAX_LARGEUR-1 )&&(fils.plateau()[j][i+1] != pere.plateau()[j][i+1]) && (fils.plateau()[j][i+1] == 'x') && pere.plateau()[j][i+1] == '0' )
                        return Brix(static_cast<int>(i+1),static_cast<int>(j),static_cast<int>(i),static_cast<int>(j));
                    return Brix();
                }
                if (fils.plateau()[j][i] == 'x') {
                    std::cout<<"OO";
                    if (( j > 0 ) && (fils.plateau()[j-1][i] != pere.plateau()[j-1][i]) && (fils.plateau()[j-1][i] == 'o') && pere.plateau()[j-1][i] == '0' )
                        return Brix(static_cast<int>(i),static_cast<int>(j),static_cast<int>(i),static_cast<int>(j-1));

                    if (( j < MAX_HAUTEUR-1 ) && (fils.plateau()[j+1][i] != pere.plateau()[j+1][i]) && (fils.plateau()[j+1][i] == 'o') && pere.plateau()[j+1][i] == '0' )
                        return Brix(static_cast<int>(i),static_cast<int>(j),static_cast<int>(i),static_cast<int>(j+1));

                    if (( i > 0 ) && (fils.plateau()[j][i-1] != pere.plateau()[j][i-1]) && (fils.plateau()[j][i-1] == 'o') && pere.plateau()[j][i-1] == '0' )
                        return Brix(static_cast<int>(i),static_cast<int>(j),static_cast<int>(i-1),static_cast<int>(j));

                    if (( i < MAX_LARGEUR-1 )&&(fils.plateau()[j][i-1] != pere.plateau()[j][i+1]) && (fils.plateau()[j][i+1] == 'o') && pere.plateau()[j][i+1] == '0' )
                        return Brix(static_cast<int>(i),static_cast<int>(j),static_cast<int>(i+1),static_cast<int>(j));

                    return Brix();
                }
            }
        }
    }
    return Brix();
}

Jeu Joueur_MonteCarlo_::etat(Narytree::Node &node)
{
    Jeu etat;
    Narytree::Node& noeudCourant(node);
    while(node.havefather()) {
        etat.joue(node.getCoup());
        noeudCourant = noeudCourant.getFather();
    }
    return etat;
}

std::vector<Brix> Joueur_MonteCarlo_::coupspossible(Jeu jeu)
{
    std::vector<Brix> coupValide;
    Brix b_canditate;
    int tour = jeu.nbCoupJoue()+1;//la b_candidate devra être valide au tour auquel on va la jouer,i.e. au tour suivant
    for (int i = 0; i<MAX_LARGEUR;i++) //i abscisse donc numero de colonne
        {
            int j=0; //j ordonnee donc numero de ligne
            while(j<MAX_HAUTEUR && jeu.plateau()[static_cast<size_t>(j)][static_cast<size_t>(i)]!='0') //dans plateau l'ordonnee en premier
                {
                    j++;
                }
            if (j<MAX_HAUTEUR)//On est tombé sur une case vide, i.e. contenant '0'
                {
                    //Cherchons des coups valides à partir de cette case vide.
                    b_canditate.setAllCoord(i,j ,i,j+1); //brix verticale dont le bottom est X
                    if (jeu.coup_licite(b_canditate,tour))
                        {
                            coupValide.push_back(b_canditate);
                        }

                    b_canditate.setAllCoord(i,j+1,i,j); //brix verticale dont le bottom est O
                    if (jeu.coup_licite(b_canditate,tour))
                        {
                            coupValide.push_back(b_canditate);
                        }

                    b_canditate.setAllCoord(i,j ,i+1,j); //brix horizontale commençant par X
                    if (jeu.coup_licite(b_canditate,tour))
                        {
                            coupValide.push_back(b_canditate);
                        }

                    b_canditate.setAllCoord(i+1,j,i,j); //brix terminant commençant par X
                    if (jeu.coup_licite(b_canditate,tour))
                        {
                            coupValide.push_back(b_canditate);
                        }
                    //fin des brix valide à cette abscisse et cette ordonnee
                }
        }//fin du for.
    return coupValide;
}

std::vector<Brix> Joueur_MonteCarlo_::coupsnonvisite(Jeu jeu, Narytree::Node &node)
{
    std::vector<Brix> coupValide = coupspossible(jeu);
    std::vector<Brix> coupnonvisite;
    for (Brix & e : coupValide) {
        size_t i=0;
        Brix b = node.getNode(0).getCoup();
       while((i<node.numberOfsons()) &&
             ((e.getAo() != b.getAo()) || (e.getAx()!=b.getAx()) || (e.getOo() != b.getOo()) || (e.getOx() != b.getOx())))
        {
                coupnonvisite.push_back(e);
                ++i;
                b = node.getNode(i).getCoup();
        }
       if ((e.getAo() != b.getAo()) || (e.getAx()!=b.getAx()) || (e.getOo() != b.getOo()) || (e.getOx() != b.getOx()))
       {
           coupnonvisite.push_back(e);
       }
    }
    return coupnonvisite;
}







