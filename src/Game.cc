#include "Game.h"
#include "Camera.h"
#include "Human.h"
#include "Node.h"
#include <iostream>
#include "GameObject.h"
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Sprite2D.h"
#include "Tree.h"
#include "PathFinding.h"
#include "Shirt.h"
#include "Faction.h"
#include "NameGenerator.h"

sf::RenderWindow Game::Window{sf::VideoMode(1920, 1080), "SFML window", sf::Style::Fullscreen};
Resources Game::resources{};
Map Game::map{64, 64};
std::vector<GameObject *> Game::gameObjects{};
std::vector<Faction *> Game::factions{};

Game::Game()
    : camera{new Camera{}}, selected{}
{
}

void Game::Run()
{
    GenerateObsticles();
    GenerateFactions();
    GenerateEnemies();
    GeneratePlayer(10, 10);
    GeneratePlayer(10, 11);

    std::cout << "Starting game..." << std::endl;
    for (auto gameObject : gameObjects)
    {
        gameObject->Start();
    }

    while (Window.isOpen())
    {
        Time::timer.restart();
        // Process events
        sf::Event event;
        while (Window.pollEvent(event))
        {
            // Close Window: exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                Window.close();
            if (event.type == sf::Event::MouseWheelMoved)
            {

                camera->CameraZoom(event.mouseWheel.delta);
                std::cout << event.mouseWheel.delta << std::endl;
            }

            sf::Vector2f mouseWorld = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
            if (isHeldDown)
            {
                selectionBox.setSize(mouseWorld - selectionBox.getPosition());
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "Left is held down!" << std::endl;
                    isHeldDown = true;
                    selectionBox.setPosition(mouseWorld);
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                //Handle left mouse click
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isHeldDown && selectionBox.getSize() != sf::Vector2f{0, 0})
                    {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
                        {
                            selected.clear();
                        }
                        bool allySelected{false};
                        for (auto gameObject : gameObjects)
                        {

                            if (gameObject->GetComponent<Sprite2D>() != nullptr)
                            {

                                if (gameObject->GetComponent<Sprite2D>()->GetSprite()->getGlobalBounds().intersects(selectionBox.getGlobalBounds()))
                                {
                                    if (gameObject->GetComponent<Human>() != nullptr)
                                    {
                                        if (gameObject->GetComponent<Human>()->faction->isPlayerFaction)
                                        {
                                            allySelected = true;
                                            selected.push_back(gameObject);
                                        }
                                        else if (!allySelected)
                                        {
                                            selected.push_back(gameObject);
                                        }
                                    }
                                }
                            }
                        }
                        isHeldDown = false;
                        std::cout << "Left is no longer held down!" << std::endl;
                        selectionBox.setSize(sf::Vector2f{0, 0});
                    }
                    else
                    {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
                        {
                            selected.clear();
                        }

                        for (auto gameObject : gameObjects)
                        {
                            if (gameObject->GetComponent<Sprite2D>() != nullptr)
                            {
                                if (gameObject->GetComponent<Sprite2D>()->GetSprite()->getGlobalBounds().contains(mouseWorld.x, mouseWorld.y))
                                {
                                    std::cout << "Clicked object!" << std::endl;
                                    selected.push_back(gameObject);
                                }
                            }
                        }
                        isHeldDown = false;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {

                    //std::cout << "Closest node(x,y) = (" << mouseWorld.x / map.mapsize.width << ", " << mouseWorld.y / map.mapsize.height << ")" << std::endl;

                    for (auto gameObject : selected)
                    {
                        if (gameObject->GetComponent<Human>() != nullptr)
                        {
                            if (gameObject->GetComponent<Human>()->faction->isPlayerFaction)
                            {
                                gameObject->GetComponent<Human>()->SetDestination(map.get_node(std::round(mouseWorld.x / map.mapsize.width), std::round(mouseWorld.y / map.mapsize.height)));
                            }
                        }
                    }
                }
            }
        }

        Update();

        Time::deltaTime = Time::timer.getElapsedTime().asSeconds();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Generate Obsticles/////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::GenerateObsticles()
{
    std::cout << "Generating Obsticles..." << std::endl;
    GameObject *obsticles{new GameObject{"Obsticles"}};
    gameObjects.push_back(obsticles);
    for (size_t i = 0; i < map.get_node_list().size(); i++)
    {

        Node *currentNode = map.get_node_list().at(i);
        if (currentNode->position.x == 0 || currentNode->position.y == 0 || currentNode->position.x == map.mapsize.width - 1 || currentNode->position.y == map.mapsize.height - 1)
        {
            currentNode->isObsticle = true;
            currentNode->marker->setFillColor(sf::Color().Red);
        }
        else if (std::rand() % 100 + 1 < 5)
        {
            std::cout << "Spawning Tree at (" << currentNode->position.x << ", " << currentNode->position.y << ")" << std::endl;
            std::cout << "Creating Gameobject..." << std::endl;
            GameObject *gameObject{new GameObject{"Tree"}};
            gameObject->parent = obsticles;
            gameObject->parent->children.push_back(gameObject);
            gameObject->transform->localPosition = currentNode->position;

            std::cout << "Creating Tree Component..." << std::endl;
            gameObject->AddComponent<Tree>();
            std::cout << "Creating Sprite2D Component..." << std::endl;
            gameObject->AddComponent<Sprite2D>((*resources.textures.find("Tree")).second);

            std::cout << "Successfully created Tree!" << std::endl;

            currentNode->isObsticle = true;
            currentNode->marker->setFillColor(sf::Color().Red);
        }
    }
    std::cout << "Obsticles generated!" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Generate Enemies///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::GenerateEnemies()
{

    std::cout << "Generating Enemies..." << std::endl
              << std::endl;
    GameObject *enemies{new GameObject{"Enemies"}};
    gameObjects.push_back(enemies);
    /* std::cout << "Spawning Human at (" << 20 << ", " << 20 << ")" << std::endl;
    std::cout << "Creating Gameobject..." << std::endl;
    GameObject *gameObject{new GameObject{"Human", map.get_node(15, 10)->position}};
    gameObject->parent = enemies;
    enemies->children.push_back(gameObject);

    std::cout << "Creating Human Component..." << std::endl;
    gameObject->AddComponent<Human>();
    std::cout << "Creating Sprite2D Component..." << std::endl;
    gameObject->AddComponent<Sprite2D>(resources.textures.at(2));
    std::cout << "Creating PathFinding Component..." << std::endl;
    gameObject->AddComponent<PathFinding>();
    gameObjects.push_back(gameObject);
    std::cout << "Successfully created human!" << std::endl; */
    for (size_t i = 0; i < map.get_node_list().size(); i++)
    {
        Node *currentNode = map.get_node_list().at(i);
        if (!currentNode->isObsticle)
        {
            if (std::rand() % 1000 + 1 < 10)
            {
                std::cout << "Spawning Human at (" << currentNode->position.x << ", " << currentNode->position.y << ")" << std::endl;
                GameObject *gameObject{new GameObject{currentNode->position}};
                std::cout << "blabla1" << std::endl;
                Human *human{gameObject->AddComponent<Human>()};
                human->name = NameGenerator::GenerateName();
                human->SetNode(currentNode);
                human->faction = factions.at(1);
                human->faction->members.push_back(human);
                std::cout << "blabla2" << std::endl;
                gameObject->AddComponent<Sprite2D>((*Resources::textures.find("Human")).second);

                enemies->children.push_back(gameObject);
                std::cout << "Successfully created human!" << std::endl;
            }
        }
    }
    std::cout << "Enemies generated!" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Generate Player////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::GeneratePlayer(int x, int y)
{
    Node *currentNode = map.get_node(x, y);
    while (map.get_node(x, y)->isObsticle)
    {
        x += 1;
        currentNode = map.get_node(x, y);
    }
    std::cout << "Spawning Player at (" << currentNode->position.x << ", " << currentNode->position.y << ")" << std::endl;
    GameObject *gameObject{new GameObject{currentNode->position}};
    std::cout << "blabla1" << std::endl;
    Human *human{gameObject->AddComponent<Human>()};
    human->name = NameGenerator::GenerateName();
    human->SetNode(currentNode);
    human->faction = factions.at(0);
    human->faction->members.push_back(human);
    std::cout << "blabla2" << std::endl;
    gameObject->AddComponent<Sprite2D>((*Resources::textures.find("Human")).second);

    //Adding Clothes
    GameObject *objectShirt{new GameObject{"Shirt", currentNode->position}};
    objectShirt->parent = gameObject;
    gameObject->children.push_back(objectShirt);
    Shirt *shirt{objectShirt->AddComponent<Shirt>()};
    objectShirt->AddComponent<Sprite2D>((*resources.textures.find("Shirt")).second);
    gameObject->GetComponent<Human>()->aparel.shirt = shirt;

    gameObjects.push_back(gameObject);
    std::cout << "Successfully created player!" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Generate Factions//////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::GenerateFactions()
{
    for (int i = 0; i < 2; i++)
    {
        Faction *faction{new Faction()};
        faction->name = "Faction" + std::to_string(i);
        factions.push_back(faction);
    }
    factions.at(0)->isPlayerFaction = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Update/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::Update()
{
    camera->CameraMovement();

    for (auto gameObject : gameObjects)
    {
        gameObject->Update();
    }

    // Clear screen
    Window.clear();
    Window.setView(camera->viewport);

    //Draw "floor"
    std::vector<Node *> nodes{map.get_node_list()};
    for (size_t i = 0; i < nodes.size(); i++)
    {

        Window.draw(*nodes.at(i)->sprite);

        //Draw Debugmarkers
        //Window.draw(*nodes.at(i)->marker);
    }
    sf::Font font{};
    font.loadFromFile("assets/ArchitectsDaughter-Regular.ttf");

    //Draw gameobject sprites
    for (auto gameObject : gameObjects)
    {
        if (gameObject->GetComponent<Sprite2D>() != nullptr)
        {
            Window.draw(*gameObject->GetComponent<Sprite2D>()->GetSprite());
        }
        for (auto child : gameObject->children)
        {
            Sprite2D *sprite{child->GetComponent<Sprite2D>()};
            if (sprite != nullptr)
            {
                sf::Sprite sp{*sprite->GetSprite()};
                sf::Vector2f pos{sp.getPosition()};
                Window.draw(sp);
            }
        }
        Entity *entity{gameObject->GetComponent<Entity>()};
        if (entity != nullptr)
        {
            sf::Text nameTag{};
            nameTag.setFont(font);
            nameTag.setString(entity->name);
            nameTag.setCharacterSize(15);
            nameTag.setOrigin(nameTag.getGlobalBounds().width / 2, nameTag.getGlobalBounds().height / 2);
            nameTag.setPosition(sf::Vector2f{gameObject->transform->position.x * 64, gameObject->transform->position.y * 64 - 34 - nameTag.getCharacterSize()});
            if (!gameObject->GetComponent<Human>()->faction->isPlayerFaction)
            {
                nameTag.setFillColor(sf::Color().Red);
            }
            Window.draw(nameTag);
        }
    }

    //Draw selected boxes
    for (auto gameObject : selected)
    {

        sf::RectangleShape box{};
        box.setSize(sf::Vector2f{64, 64});
        box.setOrigin(box.getSize().x / 2, box.getSize().y / 2);
        box.setPosition(gameObject->GetComponent<Sprite2D>()->GetSprite()->getPosition().x, gameObject->GetComponent<Sprite2D>()->GetSprite()->getPosition().y);
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Green);
        Window.draw(box);
    }

    //Draw paths
    for (auto gameObject : selected)
    {
        if (gameObject->GetComponent<Human>() != nullptr)
        {
            std::vector<PathFinding::Node *> path = gameObject->GetComponent<Entity>()->GetPath();
            if (path.size() > 0)
            {
                std::vector<sf::Vertex> lines{};
                for (auto node : path)
                {
                    sf::Vector2f vertex{node->pos.x * 64, node->pos.y * 64};
                    lines.push_back(sf::Vertex{vertex});
                    if (node == path.front())
                    {
                        sf::CircleShape endPoint{*map.get_node(node->pos.x, node->pos.y)->marker};
                        endPoint.setScale(1.5f, 1.5f);
                        endPoint.setFillColor(sf::Color().Transparent);
                        endPoint.setOutlineColor(sf::Color().White);
                        endPoint.setOutlineThickness(1);
                        Window.draw(endPoint);
                    }
                }
                for (size_t i = 0; i < lines.size() - 1; i++)
                {
                    sf::Vertex line[]{
                        lines.at(i),
                        lines.at(i + 1)};
                    Window.draw(line, 2, sf::Lines);
                }
            }
        }
    }

    //Draw selectionbox
    selectionBox.setFillColor(sf::Color::Transparent);
    selectionBox.setOutlineThickness(2);
    selectionBox.setOutlineColor(sf::Color::Green);
    Window.draw(selectionBox);

    // Update the Window
    Window.display();
}

GameObject *Game::GetGameObject(std::string name)
{
    auto result = std::find_if(gameObjects.begin(), gameObjects.end(), [&name](GameObject *object)
                               { return object->name == name; });
    if (result == gameObjects.end())
    {
        return nullptr;
    }
    return *result;
}

std::vector<Entity*> Game::GetPlayerFaction()
{
    auto result = std::find_if(Game::factions.begin(), Game::factions.end(), [](Faction *faction)
                               { return faction->isPlayerFaction; });

    return (*result)->members;
}