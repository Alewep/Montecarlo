#ifndef NARYTREE_H
#define NARYTREE_H
#include <vector>
#include "arbrecontigu.h"
#include <queue>
#include <arbrecontigu.h>
#include "../brix.hh"

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class Narytree
{

public:
    class Node
    {
    private:
        long int _val;
        long int _iterations;
        Brix _coup;
        Node  *_father;
        std::vector<Node *> _sons;
    public:
        Node(int val,int iterations, Brix const& coup);
        Node (int val,int iterations, Brix const& coup,Node &father);
        Node(Node const& node) = delete;
        ~Node() {}
        bool isaleaf() const;
        bool havefather() const ;
        long int getVal() const;
        long int getIterations () const;
        Brix getCoup() const ;
        void setVal( long int val);
        void setCoup(Brix coup);
        void setIterations(long int iterations);
        void setFather (Node &father);
        Node &get();
        const Node &getConst() const;
        void set(int val,int iterations,Brix coup);
        Node &getNode (size_t i);
        const Node &getNodeConst (size_t i) const;
        size_t numberOfsons () const ;
        Node &getFather();
        const Node& getFatherConst() const;
        void addNode(int val, int iterations,Brix coup);
        void addNode (int val,int iterations,Brix coup,Node &father);
        void erase_with_last_swap (size_t i );
    };

private:
      Node *_root;
public:
    Narytree();
    Narytree(int val,int iterations, Brix coup);
    Narytree(Narytree &n);
    Narytree(std::string const & filename, duration<double, std::milli> timetocharge);
    //Narytree(std::string const & filename);
    void toCsv (std::string const & filename) const;
    ~Narytree();
    Node &getNode();
    const Node &getNodeConst() const;
    void setNode(int val,int iterations, Brix coup);
    bool isnull() const;
    void prefixe() const;


};

#endif // NARYTREE_H
