#pragma once
#include "StaticEntity.h"
#include "Objects.h"
#include "Hitbox.h"
#include "Player.h"
#include "Border.h"
#include "Bush.h"
#include "Resource.h"
#include "SignalPool.h"
#include "PlayerController.h"
#include "EnemyController.h"
#include "KnifeManager.h"

class GameScene : public Entity {
private:
    sf :: RenderTarget* window;
public:
    GameScene(sf :: RenderTarget* window);
    virtual ~GameScene();
    virtual void update(const float& deltaTime);
};