#include "arbrecontigu.h"
#include <queue>
ArbreContigu::ArbreContigu(const std::string &filename)
{
    values = file_to_vector(filename);
}



ArbreContigu::ArbreContigu(const Binarytree &b)
{
    if (!b.isnull()) {
        std::queue<const Binarytree::Node * > qb;
        std::queue<size_t> qi;
        qi.push(1);
        qb.push(&b.getNodeConst());
        size_t tailletab = static_cast<size_t>(std::pow(2,(b.hauteur()+1)));
        //values.reserve(tailletab);
        for (size_t i = 0;i<tailletab;++i) {
            try  {
            values.push_back({0,0,true,Brix()});
            }
            catch (...) {
                std::cout<<i<<std::endl;
                break;
            }
        }
        while (!qb.empty()) {
            const Binarytree::Node * nodeb = qb.front();
            size_t i = qi.front();
            qb.pop();
            qi.pop();

            values[i-1] = {nodeb->getVal(),nodeb->getVal(),false,nodeb->getCoup()};
            if (!nodeb->leftIsNull()) {
                qb.push(&nodeb->getLeftConst());
                qi.push(i*2);
            }
            if (!nodeb->rightIsNull()) {
                qb.push(&nodeb->getRightConst());
                qi.push(i*2+1);
            }
        }
    }


}

std::vector<std::string> ArbreContigu::explode(const std::string &str, char x)
{
    std::vector<std::string> result;
    std::istringstream in(str);
    std::string token;
    while(getline(in, token, x))
        result.push_back(token);
    return result;
}



std::vector<element> ArbreContigu::file_to_vector(const std::string &filename)
{
    std::vector<element> values;
    std::string line;
    std::ifstream file(filename);
    if(!file){
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;}
    else {
        while(getline(file,line)){
            element elem;
            std::vector<std::string> vect_temp = explode(line,';');
            if (vect_temp.size() == 1)
                elem.isnull = true;
            else
            {
                elem.isnull = false;
                elem.value = std::stoi(vect_temp[0]);
                elem.iterations = std::stoi(vect_temp[1]);
                elem.brix.setAx(std::stoi(vect_temp[2]));
                elem.brix.setOx(std::stoi(vect_temp[3]));
                elem.brix.setAo(std::stoi(vect_temp[4]));
                elem.brix.setOo(std::stoi(vect_temp[5]));
                elem.brix.setDefinie(vect_temp[6]=="1" ? true : false);
            }
            values.push_back(elem);
       }
   }

        file.close();
        return values;
}

void ArbreContigu::to_csv(std::string const & filename){
    std::fstream file;
    file.open (filename, std::fstream::trunc | std::fstream::out );
    if(!file)
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    else {
        for (auto elements : values){

            if (elements.isnull)
                file << "N" << std::endl;
            else {
                file << elements.value << ";"
                << elements.iterations << ";"
                << elements.brix.getAx() << ";"
                << elements.brix.getOx() << ";"
                << elements.brix.getAo() << ";"
                << elements.brix.getOo() << ";"
                <<elements.brix.getDefinie() << std::endl;
            }

        }
    }
    file.close();


}
