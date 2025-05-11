#pragma once
#include "StaticEntity.h"
#include "Hitbox.h"
#include "Player.h"
#include "Resource.h"


class GameScene : public Entity {
private:
    sf :: RenderTarget* window;
public:
    GameScene(sf :: RenderTarget* window);
    virtual ~GameScene();
    void update(const float& deltaTime);
};