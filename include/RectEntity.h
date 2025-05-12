#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "RenderPool.h"

class RectEntity : public Entity {
private:
    sf :: FloatRect rect;
    sf :: RectangleShape outline;
public:
    RectEntity(sf :: FloatRect rect, const std :: vector<std :: string> &tag = {});
    virtual ~RectEntity();
    sf :: FloatRect getLocalRect() const;
    sf :: FloatRect getGlobalRect() const;
    void setRect(sf :: FloatRect rect);
    void render();
    virtual void update(const float &deltaTime);
};
