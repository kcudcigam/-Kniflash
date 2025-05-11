#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "SignalPool.h"

class Timer : public Entity {
private:
    float duration, currentTime;
    uint64_t receiver;
    std :: string signal;
    int content;
public:
    Timer(float duration, uint64_t receiver, const std :: string &signal, int content = 0, const std :: vector<std :: string> &tag = {});
    virtual ~Timer();
    void reset();
    bool isActive() const;
    void update(const float &deltaTime);
};
