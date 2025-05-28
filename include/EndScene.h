#pragma once
#include "StaticEntity.h"
#include "Resource.h"
#include "SignalPool.h"

class EndScene : public Entity {
public:
    EndScene(int skin, float clock, std :: pair<int, int> rank, int kills);
    virtual ~EndScene();
    virtual void update(const float& deltaTime);
};