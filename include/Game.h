#pragma once
#include <random>
#include <thread>
#include "SFML/Graphics.hpp"
#include "GameScene.h"
#include "Resource.h"
#include "RenderPool.h"
#include "SignalPool.h"
#include "EndScene.h"
#include "StartScene.h"
#include "Frame.h"

class Game {
private:
    float height, width;
    sf :: RenderWindow window;
    sf :: Event event;
    sf :: Clock clock;
    float deltaTime;
    Entity* scene = nullptr;
    
public:
    Game();
    virtual ~Game();
    void update();
    void render();
    void run();
};