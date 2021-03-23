#include "arbrecontigu.h"
#include <queue>
//ArbreContigu::ArbreContigu(const std::string &filename)
//{
//    size_t tailletab = static_cast<size_t>(10000000);
//    values.reserve(tailletab);
//    std::string line;
//    std::ifstream file(filename);
//    if(!file){
//        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;}
//    else {
//        while(getline(file,line)){
//            element elem;
//            std::vector<std::string> vect_temp = explode(line,';');
//            if (vect_temp.size() == 1)
//                elem.isnull = true;
//            else
//            {
//                elem.isnull = false;
//                elem.value = std::stoi(vect_temp[0]);
//                elem.iterations = std::stoi(vect_temp[1]);
//                elem.brix.setAx(std::stoi(vect_temp[2]));
//                elem.brix.setOx(std::stoi(vect_temp[3]));
//                elem.brix.setAo(std::stoi(vect_temp[4]));
//                elem.brix.setOo(std::stoi(vect_temp[5]));
//                elem.brix.setDefinie(vect_temp[6]=="1" ? true : false);
//            }
//            values.push_back(elem);
//       }
//   }

//   file.close();
//}



std::vector<std::string> explode(const std::string &str, char x)
{
    std::vector<std::string> result;
    std::istringstream in(str);
    std::string token;
    while(getline(in, token, x))
        result.push_back(token);
    return result;
}



