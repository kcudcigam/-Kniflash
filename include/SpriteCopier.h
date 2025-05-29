#pragma once
#include "StaticEntity.h"

class SpriteCopier : public Entity {
private:
    sf :: Sprite* sprite;
    int maxNumber;
    float interval, velocity, current = 0.f;
    int layer, order;
    bool active = true;
public:
    SpriteCopier(sf :: Sprite* sprite, int maxNumber, float interval, float velocity, int layer = 0, int order = 0, const std :: vector<std :: string> &tags = {});
    virtual ~SpriteCopier();
    void set(bool active);
    virtual void update(const float& deltaTime);
};
