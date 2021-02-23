#include "arbrecontigu.h"

ArbreContigu::ArbreContigu(const std::string &filename)
{
    values = file_to_vector(filename);
}


std::vector<std::string> Arbrecontigu::explode(const std::string & str, char x){
   std::vector<string> result;
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
                elem.isnull = vect_temp[0];
                elem.value = vect_temp[1];
                elem.b.setAx(vect_temp[2]);
                elem.b.setOx(vect_temp[3]);
                elem.b.setAo(vect_temp[4]);
                elem.b.setOo(vect_temp[5]);
                elem.b.setDefinie(vect_temp[6]);
            }        
            values.push_back(elem);
              }
        }
     }
        file.close();
        return values;
}

void ArbreContigu::to_csv(element const & e,std::string const & filename){
    std::ofstream file(filename, ios::app);
    if(!file){
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;}
    else {
        file << e.isnull << ";"<< e.value << ";" << e.b.getAx() << ";" << e.b.getOx() << ";" << e.b.getAo() << ";" << e.b.getOo() << ";" << e.b.getDefinie() << std::endl;
              }
}

