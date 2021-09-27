#ifndef RESOURCES_H
#define RESOURCES_H

class GameObject;

#include <SFML/Graphics.hpp>

#include <map>

class Resources
{
    public:
    Resources();

    static std::unordered_map<std::string,sf::Texture*> textures;

    
    private:
    void LoadTextures();
    void LoadHumanPrefab();

};



#endif