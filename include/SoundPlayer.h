#pragma once
#include "Entity.h"
#include "Resource.h"

class SoundPlayer : public Entity {
private:
    const float k = 0.0002f;
    std :: string listener;
    std :: vector<sf :: Sound*> sounds;
public:
    SoundPlayer(const std :: string &listener, const std :: vector<std :: string> &tag = {});
    virtual ~SoundPlayer();
    void play(const std :: string &name);
    virtual void update(const float &deltaTIme);
};
