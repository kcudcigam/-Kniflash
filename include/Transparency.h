#pragma once
#include "Entity.h"
#include "SignalPool.h"

class Transparency : public Entity {
private:
    uint64_t receiver;
    std :: string signal;
    float current, target;
    float duration, delay, velocity;
public:
    Transparency(uint64_t receiver, const std :: string &signal, float start, float end, float duration, float delay = 0.f, const std :: vector<std :: string> &tag = {});
    virtual ~Transparency();
    bool isActive() const;
    virtual void update(const float &deltaTime);
};
