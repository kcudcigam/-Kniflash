#pragma once
#include "Entity.h"
#include "SignalPool.h"
#include "Timer.h"
#include "Border.h"
#include "Hitbox.h"

class EnemyController : public Entity {
private:
    uint64_t cx[2], cy[2];
    float interval = 0.f;
    float delta = 0.f;
    float attackProbability = 0.f;
    const int maxn = 10;
    void move(sf :: Vector2f pos, bool reverse = false);
public:
    EnemyController(const std :: vector<std :: string> &tag = {});
    virtual ~EnemyController();
    virtual void update(const float& deltaTime);
};
