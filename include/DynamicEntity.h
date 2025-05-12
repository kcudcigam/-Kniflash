#pragma once
#include "Entity.h"
#include "Animation.h"
#include "RenderPool.h"

class DynamicEntity : public Entity {
private:
    sf :: Sprite sprite;
    int layer, order; bool fixed = false;
    std :: map<std :: string, Animation> animations;
    std :: string currentAnimation = "";
public:
    DynamicEntity(int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~DynamicEntity();
    void add(const std :: string &key, const Animation &value);
    void play(std :: string key, bool priority = false);
    virtual void update(const float& deltaTime);
};
