#include "narytree.h"



Narytree::Node::Node(int val, int iterations, const Brix &coup) : _val(val),_iterations(iterations),_coup(coup),_father(nullptr) {}

Narytree::Node::Node(int val, int iterations, const Brix &coup, Narytree::Node &father)  : _val(val),_iterations(iterations),_coup(coup),_father(&father) {}



bool Narytree::Node::isaleaf() const
{
    return _sons.empty();
}

bool Narytree::Node::havefather() const
{
    return _father != nullptr;
}

long int Narytree::Node::getVal() const
{
    return _val;
}


long int Narytree::Node::getIterations() const
{
    return _iterations;
}

Brix Narytree::Node::getCoup() const
{
    return _coup;
}

void Narytree::Node::setVal(long int val)
{
    _val = val;
}

void Narytree::Node::setCoup(Brix coup)
{
    _coup = coup;
}

void Narytree::Node::setIterations(long int iterations)
{
    _iterations = iterations;
}

void Narytree::Node::setFather(Narytree::Node &father)
{
    _father = &father;
}

Narytree::Node &Narytree::Node::get()
{
    return *this;
}

const Narytree::Node &Narytree::Node::getConst() const
{
    return *this;
}

void Narytree::Node::set(int val, int iterations, Brix coup)
{
    _val = val;
    _iterations = iterations;
    _coup = coup;
}

Narytree::Node &Narytree::Node::getNode(size_t i)
{
    return *_sons.at(i);
}

const Narytree::Node &Narytree::Node::getNodeConst(size_t i) const
{
    return *_sons.at(i);
}

size_t Narytree::Node::numberOfsons() const
{
    return _sons.size();
}

Narytree::Node &Narytree::Node::getFather()
{
    if(!havefather()) _father = new Node (0,0,Brix());
    return *_father;
}

const Narytree::Node &Narytree::Node::getFatherConst() const
{
    return *_father;
}

void Narytree::Node::addNode(int val,int iterations, Brix coup)
{
    _sons.push_back(new Node(val,iterations,coup,*this));

}

void Narytree::Node::addNode(int val, int iterations, Brix coup, Narytree::Node &father)
{
    _sons.push_back(new Node(val,iterations,coup,father));
}

void Narytree::Node::erase_with_last_swap(size_t i)
{
    if (_sons.size() > 1)
    {
        std::iter_swap(_sons.begin() + static_cast<long>(i), _sons.end() - 1);
        _sons.pop_back();
    }
    else
    {
        _sons.clear();
    }
}



Narytree::Narytree()
{
    _root = nullptr;
}


Narytree::Narytree(const std::string &filename, duration<double, std::milli> timetocharge)
//Narytree::Narytree(const std::string &filename)
{
    auto t1 = high_resolution_clock::now();
    std::string line;
    std::ifstream file(filename);
    if(!file){
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
        setNode(0,0,Brix());
    }
    else {
        getline(file,line);
        std::vector<std::string> vect_temp = explode(line,';');
        if (vect_temp.size() == 2 ) {
            std::cout<<vect_temp[0]<<std::endl;
            setNode(stoi(vect_temp[0]),stoi(vect_temp[1]),Brix());
            std::queue<Node *> noeuds;
            std::queue<size_t> indices;
            noeuds.push(&getNode());
            indices.push(0);
            size_t numeroligne = 0;
            duration<double, std::milli> ms_int = duration<double, std::milli>(0);
           while(getline(file,line) && ms_int < timetocharge  ){
            //while(getline(file,line) ){
                std::vector<std::string> vect_temp = explode(line,';');
                if (vect_temp.size() == 7 ) {
                    ++numeroligne;
                    std::stringstream sstream(vect_temp[0]);
                    size_t indicePere;
                    sstream >> indicePere;

                    while (indices.front() != indicePere){
                        indices.pop();
                        noeuds.pop();
                    }
                    Node * pere = noeuds.front();

                    pere->addNode(stoi(vect_temp[1]),stoi(vect_temp[2]),Brix(stoi(vect_temp[3]),stoi(vect_temp[4]),stoi(vect_temp[5]),stoi(vect_temp[6])),*pere);
                    noeuds.push(&pere->getNode(pere->numberOfsons()-1));
                    indices.push(numeroligne);
                }
                else {
                    setNode(0,0,Brix());
                    return;
                }
                auto t2 = high_resolution_clock::now();
                ms_int = duration<double, std::milli>(t2 - t1);
            }
            std::cout<<"nombre de noeuds chargés:"<< numeroligne;
        }
    }
}

void Narytree::toCsv(std::string const & filename) const
{

    std::fstream file;
    file.open (filename, std::fstream::trunc | std::fstream::out );
    if(!file)
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    else {
        if (!isnull()) {
            //initialisation (noeud racine)
            const Node * courant = &getNodeConst();

            file<<courant->getVal()<<";"
            <<courant->getIterations()<<std::endl;

            std::queue<const Node *> noeuds;
            std::queue<size_t> peresIndices;
            size_t plusgrand = 0;

            for (size_t i = 0 ; i< getNodeConst().numberOfsons();++i) {
                noeuds.push(&courant->getNodeConst(i));
                peresIndices.push(plusgrand);
            }
            // fin initialisation
            while (!noeuds.empty()) {
                const Node * courant = noeuds.front();
                size_t pere = peresIndices.front();
                noeuds.pop();
                peresIndices.pop();
                ++plusgrand;

                Brix coup = courant->getCoup();

                file<<pere<<";"
                <<courant->getVal()<<";"
                <<courant->getIterations()<<";"
                <<coup.getAx()<<";"
                <<coup.getOx()<<";"
                <<coup.getAo()<<";"
                <<coup.getOo()<<std::endl;


                for (size_t i = 0 ; i< courant->numberOfsons();++i) {
                    noeuds.push(&courant->getNodeConst(i));
                    peresIndices.push(plusgrand);
                }
            }

        }


    }
    file.close();

}

Narytree::Narytree(int val,int iterations, Brix coup ) :_root ( new Node(val,iterations, coup ) ) {}

Narytree::Narytree(Narytree &n)
{
    _root = n._root;
}


Narytree::~Narytree()
{
    if (!isnull()) {
        std::queue<Node *> q;
        q.push(_root);
        _root = nullptr;
        while (!q.empty()) {
            Node *node = q.front();
            q.pop();
            if(!node->isaleaf()) {
                for(size_t i = 0;i<node->numberOfsons();++i)
                {
                    q.push(&node->getNode(i));
                }
            }
            delete node;

        }
    }
}

Narytree::Node &Narytree::getNode()
{
    //if(isnull()) _root = new Node (0,0,Brix());
    return *_root;
}

const Narytree::Node &Narytree::getNodeConst() const
{
    return *_root;
}

void Narytree::setNode(int val, int iterations, Brix coup)
{
    _root = new Node(val,iterations,coup);

}

bool Narytree::isnull() const
{
    return _root == nullptr;
}

void Narytree::prefixe() const
{
    if (!isnull()) {
        std::queue<Node *> q;
        q.push(_root);
        while (!q.empty()) {
            Node *node = q.front();
            q.pop();
            if(!node->isaleaf()) {
                for(size_t i = 0;i<node->numberOfsons();++i)
                {
                    q.push(&node->getNode(i));
                }
            }
            if (node->havefather())
                std::cout<<node->getFather().getVal()<<"f";
            std::cout<<node->getVal()<<std::endl;
        }
    }
}


