#pragma once
#include "StaticEntity.h"
#include "Resource.h"
#include "SignalPool.h"
#include "Button.h"
#include "DynamicEntity.h"
#include "Transparency.h"

class EndScene : public Entity {
public:
    EndScene(sf :: RenderWindow* window, int skin, float clock, std :: pair<int, int> rank, int kills);
    virtual ~EndScene();
    virtual void update(const float& deltaTime);
};