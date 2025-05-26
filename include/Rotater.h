#pragma once
#include "Entity.h"

class Rotater : public Entity {
private:
    float velocity;
public:
    Rotater(const float &velocity, const std :: vector<std :: string> &tag = {});
    virtual ~Rotater();
    virtual void update(const float &deltaTime);
};
