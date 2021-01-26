#ifndef ARBRE_H
#define ARBRE_H
#include <vector>
#include <queue>
#include <iostream>
struct nodebinary {
    int val;
    nodebinary *right,*left;
};
using binarytree = nodebinary*;

struct nodenary {
    int val;
    std::vector<nodenary*> nodes;
};
using narytree = nodenary*;

struct value {
    bool isnull;
    int val;
};

using arraytree = std::vector<value>;
void affichertableau(arraytree const& a);
void parcourprefixe(binarytree  a);
void parcourprefixe(narytree a);
binarytree to_binarytree (arraytree a);
void to_arraytree (binarytree b , arraytree  &a );
narytree to_narytree (binarytree b);
binarytree to_binarytree (narytree b);
#endif // ARBRE_H
