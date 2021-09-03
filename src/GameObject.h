#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Component;

#include <iostream>
#include <vector>
#include <algorithm>
#include "Transform.h"
#include <functional>
#include "Game.h"

class GameObject
{
friend class Game;
public:
    //Default Constructor.
    GameObject()
        : id{Game::gameObjects.size()}, components{},name{},parent{nullptr},children{},transform{nullptr}
    {
        auto result = std::find_if(Game::gameObjects.rbegin(),Game::gameObjects.rend(),[](GameObject* object){return object->name.substr(0,10) == "GameObject";});
        if(result != Game::gameObjects.rend())
        {
            long long int number{std::distance(result,Game::gameObjects.rend())};
            name = "GameObject" + std::to_string(number);
        }
        else
        {
            name = "GameObject";
        }
        
        transform = this->AddComponent<Transform>();
    }

    //GameObject with name.
    GameObject(std::string p_name)
        : id{Game::gameObjects.size()}, components{},name{},parent{nullptr},children{},transform{nullptr}
    {
        auto result = std::find_if(Game::gameObjects.rbegin(),Game::gameObjects.rend(),[p_name](GameObject* object){return object->name.substr(0,p_name.size()) == p_name;});
        if(result != Game::gameObjects.rend())
        {
            long long int number{std::distance(result,Game::gameObjects.rend())};
            name = p_name + std::to_string(number);
        }
        else
        {
            name = p_name;
        }
        transform = this->AddComponent<Transform>();
    }

    //GameObject with position.
    GameObject(sf::Vector2f position)
        : id{Game::gameObjects.size()}, components{},name{},parent{nullptr},children{},transform{nullptr}
    {
        auto result = std::find_if(Game::gameObjects.rbegin(),Game::gameObjects.rend(),[](GameObject* object){return object->name.substr(0,10) == "GameObject";});
        if(result != Game::gameObjects.rend())
        {
            long long int number{std::distance(result,Game::gameObjects.rend())};
            name = "GameObject" + std::to_string(number);
        }
        else
        {
            name = "GameObject";
        }
        transform = AddComponent<Transform>(position);
    }

    //GameObject with name and position.
    GameObject(std::string p_name, sf::Vector2f position)
        : id{Game::gameObjects.size()}, components{},name{},parent{nullptr},children{},transform{nullptr}
    {
        auto result = std::find_if(Game::gameObjects.rbegin(),Game::gameObjects.rend(),[p_name](GameObject* object){return object->name.substr(0,p_name.size()) == p_name;});
        if(result != Game::gameObjects.rend())
        {
            long long int number{std::distance(result,Game::gameObjects.rend())};
            name = p_name + std::to_string(number);
        }
        else
        {
            name = p_name;
        }
        transform = AddComponent<Transform>(position);
    }

    //Copy Constructor.
    GameObject(const GameObject& gameObject)
    : id{gameObject.id}, components{gameObject.components},name{gameObject.name},parent{gameObject.parent}, children{gameObject.children},transform{gameObject.transform}
    {
        id = gameObject.id;
        for(auto component : gameObject.components)
        {
            AddComponent<typename
        }

    }

    GameObject& operator=(const GameObject&);

    //Add component of type <T>
    template <typename T, typename... args>
    T *AddComponent(args &&...parameters)
    {
        T *newComponent = new T{std::forward<args>(parameters)...};
        newComponent->gameObject = this;
        components.push_back(newComponent);
        return newComponent;
    }

    //Get first component of type <T>, returns nullptr if no such component is found.
    template <typename T>
    T *GetComponent()
    {
        auto result = std::find_if(components.begin(), components.end(), [](Component *component)
                                   { return (dynamic_cast<T *>(component) != nullptr); });
        if (result == components.end())
        {
            return nullptr;
        }

        return dynamic_cast<T *>(*result);
    }

    static GameObject* Instantiate(GameObject* prefab)
    {
        GameObject* gameObject{new GameObject{*prefab}};
        return gameObject;
    }

private:
    void Start()
    {
        for (auto component : components)
        {
            component->Start();
        };
    }

    void Update()
    {
        for (auto component : components)
        {
            component->Update();
        }
        for(auto child : children)
        {
            child->Update();
        }
    }
    size_t id;
    
    std::vector<Component *> components;
    public:
    std::string name;
    GameObject* parent;
    std::vector<GameObject*> children;
    Transform* transform;
};

#endif
