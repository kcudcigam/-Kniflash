#pragma once
#include <random>
#include "SFML/Graphics.hpp"

class Entity {
private:
    Entity* ancestor;
    uint64_t id;
    std :: map<std :: string, bool> tags;
    std :: map<std :: string, std :: vector<Entity*> > sub;
    std :: map<uint64_t, Entity*> ids;
    sf :: RenderWindow* window;
protected:
    std :: vector<Entity*> components;
public:
    sf :: Transform transform;
    Entity(const std :: vector<std :: string> &tag = {}, sf :: RenderWindow* window = nullptr);
    virtual ~Entity();
    Entity* super();
    Entity* root();
    uint64_t uuid() const;
    sf :: RenderWindow* getWindow() const;
    bool contains(const std :: string& tag) const;
    sf :: Transform getTransform() const;
    void addChild(Entity* child);
    std :: vector<Entity*> find(const std :: string &tag);
    Entity* find(uint64_t uuid);
    virtual void update(const float& deltaTime);
};
