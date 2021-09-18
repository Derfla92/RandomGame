#ifndef GAME_H
#define GAME_H


class Camera;
class GameObject;
class Faction;

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
    static std::vector<Faction*> factions;

    Camera* camera;
    std::vector<GameObject*> selected;
    

    private:
    
    
    void LoadPlayer();
    void Update();
    void CreateMap();
    void GenerateObsticles();
    void GenerateFactions();
    void GenerateEnemies();
    void GeneratePlayer(int, int);

    bool isHeldDown{false};
    sf::RectangleShape selectionBox{};
    

    
};

#endif