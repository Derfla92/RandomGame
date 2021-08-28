#include "PathFinding.h"
#include <iomanip>
#include "Game.h"
#include "Node.h"

PathFinding::PathFinding()
{
}

void PathFinding::Start()
{
}

void PathFinding::Update()
{
}

std::vector<PathFinding::Node *> PathFinding::construct_path_with_heap(sf::Vector2<double> &start, sf::Vector2<double> &end)
{
    //list of closed nodes already evaluated
    std::vector<Node *> closed{};
    //list of not closed nodes to be evaluated
    std::vector<Node *> open{};
    Node *currentNode{nullptr};
    Node *start_node{new Node(start)};
    Node *end_node{new Node(end)};
    std::vector<Node *> path{};
    open.push_back(start_node);

    while (open.size() > 0)
    {
        std::pop_heap(open.begin(), open.end(), [](Node *a, Node *b)
                      { return a->get_f_cost() > b->get_f_cost(); });
        currentNode = open.back();
        open.pop_back();
        closed.push_back(currentNode);

        //Check if shortest path has been found.
        if (currentNode->pos == end_node->pos)
        {
            Node *current = currentNode;
            while (current != nullptr)
            {
                path.push_back(current);
                current = current->parent;
            }
            path.pop_back();
            return path;
        }

        //Finding Children for the current node.
        std::vector<Node *> children{};

        for (int y = -1; y < 2; y++)
        {
            for (int x = -1; x < 2; x++)
            {
                if (x != 0 || y != 0)
                {
                    if (currentNode->pos.x + x < Game::map.mapsize.width && currentNode->pos.y + y < Game::map.mapsize.height)
                    {
                        if (currentNode->pos.x + x >= 0 && currentNode->pos.y + y >= 0)
                        {
                            if (!Game::map.get_node(currentNode->pos.x + x, currentNode->pos.y + y)->isObsticle)
                            {
                                Node *child = new Node(sf::Vector2<double>{currentNode->pos.x + x,currentNode->pos.y + y}, currentNode);
                                children.push_back(child);
                            }
                        }
                    }
                }
            }
        }
        for (auto &child : children)
        {
            if (contains_node_with_pos(closed, child->pos))
            {
                continue;
            }
            child->g_cost = currentNode->g_cost + 10;
            child->h_cost = pow(child->pos.x - end.x, 2) + pow(child->pos.y - end.y, 2);
            Node *node = get_node_with_pos(open, child->pos);
            if (node)
            {
                if (child->g_cost > node->g_cost)
                {
                    continue;
                }
                else
                {
                    node->g_cost = child->g_cost;
                }
                continue;
            }
            open.push_back(child);
            std::push_heap(open.begin(), open.end(), [](Node *a, Node *b)
                           { return a->get_f_cost() > b->get_f_cost(); });
        }
    }
    return path;
}

bool PathFinding::contains_node_with_pos(const std::vector<Node *> &closed_list, sf::Vector2<double> &pos)
{
    for (auto node : closed_list)
    {
        if (pos == node->pos)
        {
            return true;
        }
    }
    return false;
}

PathFinding::Node *PathFinding::get_node_with_pos(const std::vector<Node *> &nodes, sf::Vector2<double> &pos)
{
    for (auto node : nodes)
    {
        if (pos == node->pos)
        {
            return node;
        }
    }
    return nullptr;
}
