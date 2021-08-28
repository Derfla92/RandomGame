#ifndef GAME_H
#define GAME_H


class Player;
class Camera;
class GameObject;

#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Resources.h"
#include "Map.h"


class Game
{
    
    public:
    Game();
    Game(const Game&);

    Game operator=(const Game&);
    static sf::RenderWindow Window;
    void Run();

    static GameObject* GetGameObject(std::string);


    static Resources resources;
    static Map map;
    static Time time;
    static std::vector<GameObject*> gameObjects;

    Player* player;
    Camera* camera;
    std::vector<GameObject*> selected;
    

    private:
    
    
    void LoadPlayer();
    void Update();
    void CreateMap();
    void GenerateObsticles();
    void GenerateEnemies();
    void GeneratePlayer(int, int);
    

    
};

#endif