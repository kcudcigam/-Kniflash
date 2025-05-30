#pragma once
#include "Resource.h"
#include "SignalPool.h"
#include "Timer.h"
#include "Frame.h"
#include "Border.h"
#include "Hitbox.h"
#include "StaticEntity.h"

class Objects : public Entity {
private:
    const float minimalDistance = 100.f;
    const Border* border;
    int layer, order;
    const int knifeNumber = 30;
    const int speedNumber = 8;
    const int healthNumber = 4;
    bool check(sf :: Vector2f position) const;
    void set(Entity* obj) const;
public:
    Objects(const Border* border, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~Objects();
    virtual void update(const float& deltaTime);
};
