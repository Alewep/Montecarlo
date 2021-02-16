#include "arbrecontigu.h"

ArbreContigu::ArbreContigu(const std::string &filename)
{
    values = file_to_vector(filename);
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
            std::istringstream ss(line);
                   std::string word;
                   while (getline(ss, word)){
                       element elem;
                       if(word == "N")
                           elem.isnull = true;
                       else {
                           elem.isnull = false;
                           elem.value = std::stoi(word.c_str());
                       }
                       values.push_back(elem);
              }
        }
     }
        file.close();
        return values;
}

