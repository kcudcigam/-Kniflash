#pragma once
#include "Entity.h"
#include "SignalPool.h"

class EnemyController : public Entity {
private:
    uint64_t cx[2], cy[2];
    float interval = 0.f;
    float delta = 0.f;
public:
    EnemyController(const std :: vector<std :: string> &tag = {});
    virtual ~EnemyController();
    virtual void update(const float& deltaTime);
};
