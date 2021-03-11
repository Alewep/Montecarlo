#include "arbrecontigu.h"
#include <queue>
ArbreContigu::ArbreContigu(const std::string &filename)
{
    values = file_to_vector(filename);
}

static bool onlynull (std::queue<const Binarytree::Node *> q) {
    while (!q.empty()) {
        if(q.front() != nullptr) {
            return false;
        }
        q.pop();
    }
    return true;
}


ArbreContigu::ArbreContigu(const Binarytree &b)
{
    values.clear();
    Brix() ;
    const Binarytree::Node& nb = b.getNodeConst();
    if (!b.isnull())  {
        std::queue<const Binarytree::Node *> q;
        q.push(&nb);
        while (!q.empty() && !onlynull(q)) {
            const Binarytree::Node * s = q.front();
            q.pop();
            if (s == nullptr) {
                values.push_back({0,0,true,Brix()});
                q.push(nullptr);
                q.push(nullptr);
            }
            else {
                values.push_back({s->getVal(),s->getIterations(),false,s->getCoup()});
                if (!s->leftIsNull()) q.push(&s->getLeftConst());
                else q.push(nullptr);
                if (!s->rightIsNull()) q.push(&s->getRightConst());
                else q.push(nullptr);
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
