#pragma once
#include "StaticEntity.h"
#include "Resource.h"
#include "SignalPool.h"

class EndScene : public Entity {
private:
    sf :: RenderTarget* window;
public:
    EndScene(sf :: RenderTarget* window, int skin, float clock, std :: pair<int, int> rank, int kills);
    virtual ~EndScene();
    virtual void update(const float& deltaTime);
};