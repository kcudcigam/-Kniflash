#pragma once
#include "Entity.h"
#include "Resource.h"
#include "SignalPool.h"
#include "DynamicEntity.h"
#include "KnifeCircle.h"
#include "RectEntity.h"
#include "Timer.h"

class Player : public Entity {
private:
    sf :: Vector2f velocity;
    float maxVelocity = 800.f, acceleration = 3000.f, deceleration = 1500.f;
    bool direction = true;
    void move(const float &x, const float &y, const float &deltaTime);
public:
    const sf :: Vector2f base = {6794.f, 5277.f};
    const float radius = 4500.f;
    Player();
    virtual ~Player();
    void update(const float& deltaTime);
};