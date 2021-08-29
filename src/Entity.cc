#include "Entity.h"
#include "Game.h"
#include <iostream>
#include "Node.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite2D.h"

Entity::Entity()
    : Component(), node{}, adjacentNodes{}, path{}
{
}

void Entity::Start()
{
    Transform *transform{gameObject->GetComponent<Transform>()};
    node = Game::map.get_node(transform->position.x, transform->position.y);
    SetAdjacentNodes();
}

void Entity::FindDestination()
{

    //Find new destination.
    Node *destination{nullptr};

    GameObject *player{Game::GetGameObject("Player")};
    sf::Vector2<double> toPlayer{gameObject->GetComponent<Transform>()->position - player->GetComponent<Transform>()->position};
    double distanceToPlayer{std::sqrt(std::pow(toPlayer.x, 2) + std::pow(toPlayer.y, 2))};

    if (distanceToPlayer < 10)
    {
        std::vector<Node *> adjacentNodes{player->GetComponent<Entity>()->GetAdjacentNodes()};
        for (auto node : adjacentNodes)
        {
            if (!node->isObsticle)
            {
                destination = player->GetComponent<Entity>()->node;
                destination->isObsticle = false;
                SetDestination(destination);
                destination->isObsticle = true;
                return;
            }
        }
    }
    else if (path.size() == 0)
    {

        while (destination == nullptr)
        {
            int rX{std::rand() % 11 + (-5)};
            int rY{std::rand() % 11 + (-5)};
            if (node->position.x + rX > 0 && node->position.x + rX < Game::map.mapsize.width)
            {
                if (node->position.y + rY > 0 && node->position.y + rY < Game::map.mapsize.height)
                {
                    destination = Game::map.get_node(node->position.x + rX, node->position.y + rY);
                }
            }
        }
        SetDestination(destination);
    }
}

void Entity::SetDestination(Node *destinationNode)
{
    //Find new destination.
    if (!destinationNode->isObsticle)
    {
        path.clear();
        destinationNode->marker->setFillColor(sf::Color().Magenta);
        path = gameObject->GetComponent<PathFinding>()->construct_path_with_heap(node->position, destinationNode->position);
    }
}

std::vector<PathFinding::Node *> Entity::GetPath()
{
    return path;
}

void Entity::Movement()
{

    if (path.size() > 0)
    {
        if(Game::map.get_node(path.back()->pos.x,path.back()->pos.y)->isObsticle)
        {
            FindDestination();
        }
        else if (path.back()->pos != Game::GetGameObject("Player")->GetComponent<Entity>()->node->position)
        {
            sf::Vector2<double> movement{path.back()->pos - gameObject->GetComponent<Transform>()->position};

            double length{std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2))};
            //Normalize movementvector
            movement = {movement.x / length, movement.y / length};
            //Check if we reached an acceptable distance to node's middle.
            double stepDistance{std::sqrt(std::pow(movement.x * speed * Time::deltaTime, 2) + std::pow(movement.y * speed * Time::deltaTime, 2))};
            sf::Vector2<double> playerVector{path.back()->pos - gameObject->GetComponent<Transform>()->position};
            double distancePlayerToNode{std::sqrt(std::pow(playerVector.x, 2) + std::pow(playerVector.y, 2))};
            if (distancePlayerToNode > stepDistance)
            {
                //Apply movement
                gameObject->GetComponent<Sprite2D>()->GetSprite()->move(movement.x * speed * Time::deltaTime, movement.y * speed * Time::deltaTime);
                gameObject->GetComponent<Transform>()->position += sf::Vector2<double>{(movement.x * speed * Time::deltaTime), (movement.y * speed * Time::deltaTime)};
            }
            else
            {
                node->isObsticle = false;
                node = Game::map.get_node(path.back()->pos.x, path.back()->pos.y);
                node->isObsticle = true;
                //Grab new adjacent nodes and color them.
                SetAdjacentNodes();
                node->marker->setFillColor(sf::Color().Yellow);
                path.pop_back();
            }
        }
    }
}

void Entity::Attack()
{
    GameObject* player{Game::GetGameObject("Player")};
    for(auto node : adjacentNodes)
    {
        if(player->GetComponent<Entity>()->node == node && attackTimer <= sf::seconds(0))
        {
            std::cout << gameObject->name << " is attacking Player!" << std::endl;
            attackTimer = attackSpeed;
            return;
        }
    }
    if(attackTimer > sf::seconds(0))
    {
        attackTimer -= sf::seconds(Time::deltaTime);
    }
}

void Entity::SetAdjacentNodes()
{
    //std::cout << "Removing old Adjacent nodes..." << std::endl;
    for (size_t i = 0; i < adjacentNodes.size(); i++)
    {
        if (adjacentNodes.at(i)->isObsticle)
        {
            adjacentNodes.at(i)->marker->setFillColor(sf::Color().Red);
        }
        else
        {
            adjacentNodes.at(i)->marker->setFillColor(sf::Color().Green);
        }
    }
    adjacentNodes.clear();
    //std::cout << "Nodes cleared!" << std::endl;
    //std::cout << "Finding Adjacent nodes..." << std::endl;

    for (int y = -1; y < 2; y++)
    {
        for (int x = -1; x < 2; x++)
        {

            Node *adjacentNode{Game::map.get_node(node->position.x + x, node->position.y + y)};
            adjacentNode->marker->setFillColor(sf::Color().Cyan);
            adjacentNodes.push_back(adjacentNode);
        }
    }

    //std::cout << "Adjacent nodes found!" << std::endl;
}

std::vector<Node *> Entity::GetAdjacentNodes()
{
    return adjacentNodes;
}