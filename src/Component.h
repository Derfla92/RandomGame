#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
    friend class GameObject;
    public:
    Component();
    Component(const Component&);
    virtual ~Component() = default;

    Component& operator=(const Component&);
    GameObject* gameObject;
    
    protected:
    virtual void Update() = 0;
    virtual void Start() = 0;
    
};

#endif