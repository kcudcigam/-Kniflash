#pragma once
#include "StaticEntity.h"
#include "Border.h"
#include "SignalPool.h"
#include "Player.h"

class Minimap : public Entity {
private:
    const Border* border;
    int size; float radius, circleSize;
    const float d = 8.f;
    bool active = true;
public:
    Minimap(const Border* border, int size, const std :: vector<std :: string> &tag = {});
    virtual ~Minimap();
    void hide();
    virtual void update(const float& deltaTime);
};
