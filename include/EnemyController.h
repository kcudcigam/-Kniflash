#pragma once
#include "Entity.h"
#include "SignalPool.h"
#include "Timer.h"

class EnemyController : public Entity {
private:
    uint64_t cx[2], cy[2];
    float interval = 0.f;
    float delta = 0.f;
    uint64_t target = 0;
public:
    EnemyController(const std :: vector<std :: string> &tag = {});
    virtual ~EnemyController();
    virtual void update(const float& deltaTime);
};
