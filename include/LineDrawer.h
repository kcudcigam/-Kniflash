#pragma once
#include "StaticEntity.h"

class LineDrawer : public Entity {
private:
    const float radius = 5.f;
    std :: vector<Entity*> rub;
public:
    LineDrawer(const std :: vector<std :: string> &tag = {});
    virtual ~LineDrawer();
    void draw(const sf :: Vector2f &start, const sf :: Vector2f &end, float delta, int layer = 0, int order = 0); 
    virtual void update(const float& deltaTime);
};
