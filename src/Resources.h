#ifndef RESOURCES_H
#define RESOURCES_H

class GameObject;

#include <SFML/Graphics.hpp>

#include <map>

class Resources
{
    public:
    Resources();

    std::unordered_map<std::string,sf::Texture*> textures;
    std::unordered_map<std::string,GameObject*> prefabs;
    
    private:
    void LoadTextures();
    void LoadHumanPrefab();

};



#endif