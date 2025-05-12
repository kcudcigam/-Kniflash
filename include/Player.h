#pragma once
#include <random>
#include "Entity.h"
#include "Resource.h"
#include "SignalPool.h"
#include "DynamicEntity.h"
#include "HealthBar.h"
#include "KnifeCircle.h"
#include "RectEntity.h"
#include "Border.h"
#include "Timer.h"

class Player : public Entity {
private:
    const Border* border;
    sf :: Vector2f velocity;
    float maxVelocity = 800.f, acceleration = 3000.f, deceleration = 1500.f;
    bool direction = true;
    void move(const float &x, const float &y, const float &deltaTime);
public:
    Player(const Border* border = nullptr, const std :: vector<std :: string> &tag = {});
    virtual ~Player();
    virtual void update(const float& deltaTime);
};