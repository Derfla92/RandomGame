#include "Resources.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "Human.h"
#include "GameObject.h"
#include "Sprite2D.h"
#include "Faction.h"

namespace fs = std::filesystem;

Resources::Resources()
    : textures{}, prefabs{}
{
    LoadTextures();
    LoadHumanPrefab();
}

void Resources::LoadTextures()
{
    // Load Textures

    std::string path{"assets/"};
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.path().extension() == ".png")
        {
            std::cout << "Found .png file" << std::endl;
            std::cout << entry.path().generic_string() << std::endl;
            std::cout << entry.path().stem().string() << std::endl;
            sf::Texture *texture{new sf::Texture{}};
            texture->loadFromFile(entry.path().generic_string());
            textures.insert({entry.path().stem().string(), texture});
        }
    }
}

void Resources::LoadHumanPrefab()
{
    std::cout << "Loading Human Prefab..." << std::endl;
    std::cout << "Creating GameObject..." << std::endl;
    GameObject *gameObject{new GameObject{"Human"}};
    std::cout << "Adding Human Component..." << std::endl;
    gameObject->AddComponent<Human>();
    std::cout << "Adding Faction Component..." << std::endl;
    gameObject->AddComponent<Faction>();
    std::cout << "Adding Sprite2D Component with Human texture..." << std::endl;
    gameObject->AddComponent<Sprite2D>((*textures.find("Human")).second);
    std::cout << "Adding PathFinding Component..." << std::endl;
    gameObject->AddComponent<PathFinding>();

    prefabs.insert({"Human",gameObject});

    std::cout << "Finished loading Human Prefab!" << std::endl;
}
