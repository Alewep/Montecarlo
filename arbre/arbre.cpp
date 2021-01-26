#include "arbre.h"

void affichertableau(arraytree const& a) {
    for ( auto const &e : a) {
        if (e.isnull == true) std::cout<<"null|";
        else std::cout<<e.val<<"|";
    }
    std::cout<<std::endl;
}

void parcourprefixe(binarytree  a) {
    if (a != nullptr) {
        std::cout<<a->val<<"|";
        std::cout<<"l :";
        parcourprefixe(a->left);
        std::cout<<"r :";
        parcourprefixe(a->right);
    }

}
void parcourprefixe(narytree a) {
    if (a !=nullptr) {
        std::cout<<a->val<<"|";
        std::cout<<a->nodes.size()<<std::endl;
        for (auto const&e : a->nodes) {
            parcourprefixe(e);

        }
    }
}




// fonction pour convertir un tableau en arbre binaire
binarytree to_binarytree_indice (arraytree a,unsigned int i)// i commence  à 1
{
    if (i<= a.size() && a[i-1].isnull == false) {
        binarytree b = new nodebinary;
        b->val = a[i-1].val;
        b->left = to_binarytree_indice(a,i*2);
        b->right = to_binarytree_indice(a,i*2+1);
        return b;
    }
    else return nullptr;
}

binarytree to_binarytree (arraytree a){
    return to_binarytree_indice (a,1); // commence à partir du premier element du tableau
}

// fonction pour convertir un arbre binaire en tableau
bool onlynull (std::queue<binarytree> q) {
    while (!q.empty()) {
        if(q.front() != nullptr ) {
            return false;
        }
        q.pop();
    }
    return true;
}

void to_arraytree (binarytree b , arraytree  &a ){
    if (b != nullptr)  {
        std::queue<binarytree> q;
        q.push(b);
        while (!q.empty() && !onlynull(q)) {
            binarytree s = q.front();
            q.pop();
            if (s == nullptr) {
                a.push_back({true,0});
                q.push(nullptr);
                q.push(nullptr);
            }
            else {
                a.push_back({false,s->val});
                q.push(s->left);
                q.push(s->right);
            }
        }
    }
}
//fonction pour convertir un arbre binaire en arbre n-aire

narytree to_narytree (binarytree b) {
    if (b != nullptr) {
        narytree node = new nodenary;
        node->val = b->val;
        binarytree courant = b->left;
        while (courant != nullptr)
        {
            node->nodes.push_back(to_narytree(courant));
            courant = courant->right;
        }
        return node;
    }
    else return nullptr;
}

binarytree to_binarytree (narytree b){
    if (b != nullptr)
    {
        binarytree node = new nodebinary;
        node->val = b->val;
        if(b->nodes.size() !=0 ) {
            node->left = to_binarytree(b->nodes.at(0));
            binarytree courant = node->left;
            for(auto const&e : b->nodes) {
                courant->right = to_binarytree(e);
                courant = courant->right;
            }
        }
        return node;
    }
    else return nullptr;
}

