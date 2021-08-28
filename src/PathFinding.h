#ifndef PATHFINDING_H
#define PATHFINDING_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <map>
#include "Component.h"

class PathFinding : public Component
{
public:

    void Start() override;
    void Update() override;
    static constexpr int diagonal_weight{14};
    static constexpr int side_weight{10};

    struct Node
    {
        Node() : pos{},parent{}{};
        Node(const PathFinding::Node&);
        Node(sf::Vector2<double> position, Node *parent = nullptr) : pos{position}, parent(parent){};
        ~Node()
        {
            std::cout << "Deleting node." << std::endl;
        }

        Node operator=(const Node&);
        sf::Vector2<double> pos;
        Node *parent;

        int g_cost{};
        int h_cost{};
        int get_f_cost()
        {
            return g_cost + h_cost;
        }
    };
    PathFinding();
    
    std::vector<Node *> construct_path_with_heap(sf::Vector2<double> &, sf::Vector2<double> &);
    private:
    bool contains_node_with_pos(const std::vector<Node *> &, sf::Vector2<double> &);
    Node *get_node_with_pos(const std::vector<Node *> &, sf::Vector2<double> &);
    
};

#endif