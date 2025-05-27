#pragma once
#include "StaticEntity.h"
#include "Resource.h"
#include "SignalPool.h"
#include "Player.h"
#include "Border.h"
#include "Bush.h"
#include "EnemyController.h"
#include "KnifeManager.h"

class StartScene : public Entity {
private:
    sf :: RenderTarget* window;
    const int enemyCount = 6;
public:
    StartScene(sf :: RenderTarget* window);
    virtual ~StartScene();
    virtual void update(const float& deltaTime);
};