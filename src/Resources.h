#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>



class Resources
{
    public:
    Resources();

    std::vector<sf::Texture*> textures;
    void LoadTextures();
    private:

};



#endif