#pragma once
#include "Entity.h"
#include "Resource.h"
#include "DynamicEntity.h"
#include "KnifeCircle.h"

class Player : public Entity {
private:
    sf :: Vector2f velocity;
    float maxVelocity = 800.f, acceleration = 3000.f, deceleration = 1500.f;
    bool direction = true;
    void move(const float &x, const float &y, const float &deltaTime);
public:
    Player();
    virtual ~Player();
    void update(const float& deltaTime);
};