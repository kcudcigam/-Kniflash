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
#include "Rotater.h"
#include "FlyKnife.h"
#include "Statistics.h"
#include "KillNumber.h"
#include "SpriteCopier.h"
#include "EllipseShape.h"
#include "ShapeCopier.h"

class Player : public Entity {
private:
    const Border* border;
    sf :: Vector2f velocity;
    float maxVelocity = 800.f, acceleration = 3000.f, deceleration = 1500.f;
    bool direction = true, active = true, dead = false;
    uint64_t attacker = 0; int skin = 0;
    bool interactive;
    void attack(const sf :: Vector2f &u);
    void combat();
    void hurt();
    void move(const float &x, const float &y, const float &deltaTime);
    uint64_t nearest();
public:
    Player(const Border* border = nullptr, const std :: vector<std :: string> &tag = {}, bool interactive = true);
    virtual ~Player();
    void hide();
    bool isActive() const;
    bool isDead() const;
    int getSkin() const;
    virtual void update(const float& deltaTime);
};