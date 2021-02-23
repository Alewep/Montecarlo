#ifndef ARBRECONTIGU_H
#define ARBRECONTIGU_H
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "arbrebin.h"
#include "brix.hh"
struct element{
    int value;
    bool isnull;
    Brix brix;
};

class ArbreContigu
{
private:
    std::vector<element> values;
    std::vector<element> file_to_vector(const std::string & filename);

public:
    ArbreContigu(const std::string & filename);
    ArbreContigu(Binarytree const& b); // a définir (! sans recursivité)
    std::vector<element> getvalues() {return values;}
    std::vector<std::string> explode(const std::string & str, char x);
    void to_csv(element const & e,std::string const & string);


#endif // ARBRECONTIGU_H
