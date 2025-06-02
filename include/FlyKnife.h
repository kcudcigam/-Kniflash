#pragma once
#include "Frame.h"
#include "StaticEntity.h"
#include "RenderPool.h"
#include "Resource.h"
#include "SignalPool.h"
#include "SpriteCopier.h"

class FlyKnife : public Entity {
private:
    uint64_t owner;
    sf :: Vector2f pos, v;
    const float velocity = 4500.f, maxd = 1500.f;
    float delta = 0.f;

public:
    FlyKnife(uint64_t owner, const sf :: Vector2f &pos, const sf :: Vector2f &v, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~FlyKnife();
    bool isActive() const;
    virtual void update(const float& deltaTime);
};
