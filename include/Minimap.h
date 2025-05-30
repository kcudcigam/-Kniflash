#pragma once
#include "StaticEntity.h"
#include "Border.h"
#include "SignalPool.h"
#include "Player.h"

class Minimap : public Entity {
private:
    const Border* border;
    int size; float radius;
    const float d = 4.f;
public:
    Minimap(const Border* border, int size, const std :: vector<std :: string> &tag = {});
    virtual ~Minimap();
    virtual void update(const float& deltaTime);
};
