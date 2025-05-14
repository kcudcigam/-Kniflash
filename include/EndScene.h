#pragma once
#include "StaticEntity.h"
#include "Resource.h"
#include "SignalPool.h"

class EndScene : public Entity {
private:
    sf :: RenderTarget* window;
public:
    EndScene(sf :: RenderTarget* window);
    virtual ~EndScene();
    virtual void update(const float& deltaTime);
};