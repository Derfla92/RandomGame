#ifndef MAP_H
#define MAP_H

class Node;

#include <SFML/Graphics.hpp>


class Map
{
    public:
    Map(int,int);

    Node* get_node(int,int);
    std::vector<Node*>& get_node_list();
    struct size{
        int width{10};
        int height{10};
    }const mapsize;
    private:
    
    std::vector<Node*> nodes;

};

#endif