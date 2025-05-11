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
    const Border* border;
    int layer, order;
    const int knifeNumber = 25;
    const int speedNumber = 10;
    //const int healthNumber = 10;
public:
    Objects(const Border* border, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~Objects();
    void update(const float& deltaTime);
};
