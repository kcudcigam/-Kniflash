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
#include "EndScene.h"
#include "Transparency.h"
#include "LineDrawer.h"

class GameScene : public Entity {
private:
    float clock = 0.f;
    const int enemyCount = 40;
public:
    std :: tuple<int, float, std :: pair<int, int>, int> data();
    GameScene(sf :: RenderWindow* window);
    virtual ~GameScene();
    virtual void update(const float& deltaTime);
};