#include "joueur_montecarlo_.hh"
const double Joueur_MonteCarlo_::PONDERATION(2.0);

Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur),_tree(ArbreContigu("tree_montecarlo_OAA.txt")),_courant(_tree.getNode()) {

    std::cout<<"succes..."<<std::endl;
}

void Joueur_MonteCarlo_::savetree()
{
    _tree.prefixe();
    _tree.toCsv("tree_montecarlo_OAA.txt");
    std::cout<<"done";
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
                if(fils.plateau()[j][i] == 'o') {
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


double Joueur_MonteCarlo_::uperboundconfidence(Narytree::Node &node)
{
   if(node.getIterations()) return (node.getVal()/node.getIterations()) + sqrt(PONDERATION*(log(node.getFather().getVal())/node.getIterations()));
   else return DBL_MAX;
}

Jeu Joueur_MonteCarlo_::etat( const Narytree::Node &node)
{
    Jeu etat;
    const Narytree::Node * noeudCourant = &node;
    while(noeudCourant->havefather()) {
        etat.joue(noeudCourant->getCoup());
        noeudCourant = &noeudCourant->getFatherConst();
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

bool Joueur_MonteCarlo_::coupvisite(Brix b, Narytree::Node &node)
{
    for (size_t i = 0;i<node.numberOfsons();++i)
    {
        if (
            b.getAo() == node.getNode(i).getCoup().getAo() &&
            b.getAx() == node.getNode(i).getCoup().getAx() &&
            b.getOo() == node.getNode(i).getCoup().getOo() &&
            b.getOx() == node.getNode(i).getCoup().getOx()
        ) return true;
    }
    return false;
}

std::vector<Brix> Joueur_MonteCarlo_::coupsnonvisites(Narytree::Node &node)
{
    std::vector<Brix> coupValide = coupspossible(etat(node));
    std::vector<Brix> coupnonvisite;
    if ( node.numberOfsons() != 0) {
        for (Brix & e : coupValide) {
           if(!coupvisite(e,node)) coupnonvisite.push_back(e);
        }
        return coupnonvisite;
    }
    return coupValide;
}

Narytree::Node& Joueur_MonteCarlo_::maxUBC(Narytree::Node& node) // renvoie parmi les fils du noeud appelé celui qui maximise UBC
{
    Narytree::Node * current_node = & node;
    Narytree::Node * best_child =&current_node->getNode(0);
    double max = uperboundconfidence(*best_child);
    for (size_t i=1;i<current_node->numberOfsons();i++)
    {
        double calcl = uperboundconfidence(current_node->getNode(i));
        if(calcl>max)
        {
            best_child = &current_node->getNode(i);
            max = calcl;

        }
        else if (abs(calcl - max) > 0.000001)
        {
           int choix = rand() % 1;
           if (choix == 0) {
               best_child = &current_node->getNode(i);
               max = calcl;
           }
        }
    }
    return *best_child;
}


Narytree::Node& Joueur_MonteCarlo_::descent(Narytree::Node& node)
{
    Narytree::Node * current_node =&node;
    while ((coupsnonvisites(*current_node).empty()) && (current_node->numberOfsons()>0))
        current_node = &maxUBC(*current_node);

    return *current_node;
}

Narytree::Node &Joueur_MonteCarlo_::growth(Narytree::Node &node)
{
    // creer un nouveau noeud parmis les succeur de l'etat etiquetant la feuille
    std::vector<Brix> cnv = coupsnonvisites(node);
    //    std::cout<<"--------"<<std::endl;
    //    if(node.havefather()) std::cout<<etat(node.getFatherConst())<<std::endl;
    //    else std::cout<<"pas de pere"<<std::endl;
    //    std::cout<<etat(node)<<std::endl;
    //    std::cout<<"cnv"<<!cnv.empty()<<std::endl;
    if (!cnv.empty())
    {
        size_t rand_int;
        if (cnv.size() != 1) rand_int = static_cast<size_t>(rand () % static_cast<int>(cnv.size() - 1) + 0);
        else rand_int = 0;
        node.addNode(0,0,cnv[rand_int],node);
        return node.getNode(node.numberOfsons()-1);
    }
    return node;
}

int Joueur_MonteCarlo_::rollout(Narytree::Node &node)
{

    Jeu current_game = etat(node);
    std::vector<Brix> cp = coupspossible(current_game);
    while (!current_game.fini() && !cp.empty()){

        size_t rand_int = static_cast<size_t>(rand() % static_cast<int>(cp.size() - 1) + 0); // coupspossible.size() >= 1 car partie non finie
        current_game.joue(cp[rand_int]);
         std::vector<Brix> cp = coupspossible(current_game);
    }
    if (current_game.partie_X()) //on choisit arbitrairement +1 pour les croix et -1 pour O
        return  1;
    if (current_game.partie_O())
        return -1;
    if (current_game.partie_nulle())
        return 0;
    return 0;
}

void Joueur_MonteCarlo_::update(Narytree::Node &node, int val)
{
    Narytree::Node * nodeCourant = &node;
    while(nodeCourant->havefather()){
        nodeCourant->setIterations(nodeCourant->getIterations()+1);
        nodeCourant->setVal(nodeCourant->getVal()+val);
        nodeCourant = &nodeCourant->getFather();
    }
    //modification racine
    nodeCourant->setIterations(nodeCourant->getIterations()+1);
    nodeCourant->setVal(nodeCourant->getVal()+val);
}

void Joueur_MonteCarlo_::montecarlo()
{
    //std::cout<<"test"<<std::endl;
    Narytree::Node& des = descent(_courant);
    Narytree::Node& gro = growth(des);
    int res = rollout(gro);
    update(gro,res);
}









