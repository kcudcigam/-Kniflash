#pragma once
#include "SFML/Graphics.hpp"
#include "Frame.h"

class Animation {
private:
    float currentTime, duration;
    std :: vector<Frame> list;
    size_t it;
    bool loop, paused;
public:
    Animation(const std :: vector<Frame> &list = (std :: vector<Frame>){}, const float &duration = 0, bool loop = true);
    virtual ~Animation();
    void setLoop(bool loop = true);
    void pause();
    void run();
    bool end() const;
    void play(sf :: Sprite *sprite, const float &deltaTime);
    void reset();
};
