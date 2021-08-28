#include "Resources.h"
#include <iostream>

Resources::Resources()
    : textures{}
{
    LoadTextures();
}

void Resources::LoadTextures()
{
    // Load Textures

    //Player
    sf::Texture *playerTxt{new sf::Texture{}};
    if (playerTxt->loadFromFile("assets/Player.png"))
    {
        textures.push_back(playerTxt);
        std::cout << "Successfully loaded Player Texture!" << std::endl;
    }

    //Tree
    sf::Texture *treeTxt{new sf::Texture{}};
    if (treeTxt->loadFromFile("assets/Tree.png"))
    {
        textures.push_back(treeTxt);
        std::cout << "Successfully loaded Tree Texture!" << std::endl;
    }

    //Ghost
    sf::Texture *ghostTxt{new sf::Texture{}};
    if (ghostTxt->loadFromFile("assets/Ghoul.png"))
    {
        textures.push_back(ghostTxt);
        std::cout << "Successfully loaded Ghost Texture!" << std::endl;
    }

    //Grass
    sf::Texture *grassTxt{new sf::Texture{}};
    if (grassTxt->loadFromFile("assets/Grass.png"))
    {
        textures.push_back(grassTxt);
        std::cout << "Successfully loaded Grass Texture!" << std::endl;
    }
}