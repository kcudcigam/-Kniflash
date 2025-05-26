#pragma once
#include "Frame.h"
#include "StaticEntity.h"
#include "RenderPool.h"
#include "Resource.h"
#include "SignalPool.h"

class FlyKnife : public Entity {
private:
    sf :: Vector2f pos, v;
    const float velocity = 4500.f, maxd = 1000.f;
    float delta = 0.f;
public:
    FlyKnife(const sf :: Vector2f &pos, const sf :: Vector2f &v, const std :: vector<std :: string> &tag = {});
    virtual ~FlyKnife();
    virtual void update(const float& deltaTime);
};
