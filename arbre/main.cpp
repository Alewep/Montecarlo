#include <iostream>
#include "arbre.h"
using namespace std;

int main()
{
    arraytree a = {{false,1},{true,0},{false,2},{true,0},{true,0},{false,3},{false,0},};
    //affichertableau(a);
    binarytree b = to_binarytree(a);
    parcourprefixe(b);
    a.clear();
    std::cout<<std::endl;
    to_arraytree(b,a);
    narytree n = to_narytree(b);
    parcourprefixe(n);
    //affichertableau(a);

}
