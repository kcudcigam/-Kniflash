#pragma once
#include "StaticEntity.h"
#include "Frame.h"
#include "Resource.h"
#include "SignalPool.h"
#include "RenderPool.h"

class HealthBar : public Entity {
private:
    uint64_t owner;
    int layer, order;
    const int maxHealth = 5;
    int health = maxHealth;
public:
    HealthBar(uint64_t owner, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~HealthBar();
    void add();
    void inc();
    void recover();
    virtual void update(const float &deltaTime);
};
