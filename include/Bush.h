#pragma once
#include "StaticEntity.h"
#include "Resource.h"
#include "Border.h"

class Bush : public Entity {
private:
    const float minimalDistance = 1000.f;
    const Border* border;
    int number, layer, order;
    bool check(sf :: Vector2f position) const;
public:
    Bush(const Border* border, int number, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~Bush();
    void set(int number);
};