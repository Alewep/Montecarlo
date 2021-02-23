#include "arbrecontigu.h"

ArbreContigu::ArbreContigu(const std::string &filename)
{
    values = file_to_vector(filename);
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
            else {
                elem.isnull = false;
                elem.value = std::stoi(vect_temp[1]);
                elem.brix.setAx(std::stoi(vect_temp[2]));
                elem.brix.setOx(std::stoi(vect_temp[3]));
                elem.brix.setAo(std::stoi(vect_temp[4]));
                elem.brix.setOo(std::stoi(vect_temp[5]));
                elem.brix.setDefinie(vect_temp[6]=="1" ? 1 : 0);
            }
            values.push_back(elem);
              }
        }

        file.close();
        return values;
}

void ArbreContigu::to_csv(std::string const & filename){
    std::ofstream file(filename, std::ios::app);
    if(!file){
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;}
    else {
        for (auto elements : values){
            if (elements.isnull)
                file << "N;" << std::endl;
            else
            file << elements.isnull << ";"<< elements.value << ";" << elements.brix.getAx() << ";" << elements.brix.getOx() << ";" << elements.brix.getAo() << ";" << elements.brix.getOo() << ";" <<elements.brix.getDefinie() << std::endl;
        }

              }
}
