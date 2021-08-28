#include "Map.h"
#include "Node.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

Map::Map(int width,int height)
: mapsize{width,height}, nodes{}
{
    std::cout << "Creating map..." << std::endl;
    for (int y = 0; y < mapsize.height; y++)
    {
        for (int x = 0; x < mapsize.width; x++)
        {

            Node* node{new Node{}};
            node->position = sf::Vector2<double>(x, y);

            sf::CircleShape* marker{new sf::CircleShape{10}};
            marker->setFillColor(sf::Color().Green);
            marker->setOrigin(marker->getRadius(), marker->getRadius());
            sf::Vector2<double> position{node->position.x * 64, node->position.y * 64};
            marker->setPosition(position.x, position.y);
            node->marker = marker;

            sf::Sprite* grass{new sf::Sprite{}};
            grass->setTexture(*Game::resources.textures.at(3));
            grass->setOrigin(Game::resources.textures.at(3)->getSize().x/2,Game::resources.textures.at(3)->getSize().y/2);
            grass->setScale(0.125f,0.125f);
            grass->setPosition(position.x, position.y);
            node->sprite = grass;

            nodes.push_back(node);
        }
    }
    std::cout << "Successfully created map with " << nodes.size() << " nodes."<< std::endl;
}

Node* Map::get_node(int x,int y)
{
    return nodes.at(x+(y*mapsize.width));
}

std::vector<Node*>& Map::get_node_list()
{
    return nodes;
}