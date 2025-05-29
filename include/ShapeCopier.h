#pragma once
#include "StaticEntity.h"
#include "EllipseShape.h"

class ShapeCopier : public Entity {
private:
    sf :: Shape* shape;
    int maxNumber;
    float interval, velocity, current = 0.f;
    int layer, order;
    bool active = true;
public:
    ShapeCopier(sf :: Shape* sprite, int maxNumber, float interval, float velocity, int layer = 0, int order = 0, const std :: vector<std :: string> &tags = {});
    virtual ~ShapeCopier();
    void set(bool active);
    virtual void update(const float& deltaTime);
};
