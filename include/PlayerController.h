#pragma once
#include "Entity.h"
#include "SignalPool.h"
#include "Timer.h"

class PlayerController : public Entity {
public:
    PlayerController(const std :: vector<std :: string> &tag = {});
    virtual ~PlayerController();
    virtual void update(const float& deltaTime);
};
