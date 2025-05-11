#pragma once
#include "SFML/Graphics.hpp"
#include "RectEntity.h"
#include "SignalPool.h"

class Hitbox : public RectEntity {
private:
    std :: string target;
    std :: string signal;
    int content;
    bool active = true;
public:
    Hitbox(sf :: FloatRect rect, const std :: string &target, const std :: string &signal, int content = 0, const std :: vector<std :: string> &tag = {});
    virtual ~Hitbox();
    void reset();
    bool isActive() const;
    void update(const float &deltaTime);
};
