#ifndef ARBRECONTIGU_H
#define ARBRECONTIGU_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include "arbrebin.h"
#include "../brix.hh"

struct element{
    int value;
    int iterations;
    bool isnull;
    Brix brix;
};

class ArbreContigu
{
private:
    std::vector<element> file_to_vector(const std::string & filename);
    std::vector<std::string> explode(const std::string & str, char x);

public:
    std::vector<element> values;
    ArbreContigu(const std::string & filename);
    ArbreContigu(Binarytree const& b); // a définir (! sans recursivité)
    std::vector<element> getvalues() const {return values;}
    void to_csv(std::string const & filename);

};
#endif // ARBRECONTIGU_H
