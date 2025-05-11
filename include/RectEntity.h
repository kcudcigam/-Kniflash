#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "RenderPool.h"

class RectEntity : public Entity {
private:
    sf :: FloatRect rect;
    std :: vector<sf :: RectangleShape * > outlines;
public:
    RectEntity(sf :: FloatRect rect);
    virtual ~RectEntity();
    sf :: FloatRect getRect() const;
    void setRect(sf :: FloatRect rect);
    void render();
    void update(const float &deltaTime);
};
