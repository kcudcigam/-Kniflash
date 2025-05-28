#pragma once
#include "Entity.h"
#include "RenderPool.h"

class StaticEntity : public Entity {
private:
    sf :: Drawable* obj;
    int layer, order;
    bool active = true;
public:
    StaticEntity(sf :: Drawable *obj = nullptr, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~StaticEntity();
    void set(sf :: Drawable *obj);
    void setStatus(bool status);
    sf :: Drawable* get();
    virtual void update(const float& deltaTime);
};
