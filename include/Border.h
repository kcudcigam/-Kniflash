#pragma once
#include <random>
#include "StaticEntity.h"
#include "SignalPool.h"

class Border : public Entity {
private:
    sf :: Vector2f base;
    float radius;
    int layer, order;
    const float velocity = 100.f;
public:
    Border(sf :: Vector2f base, float radius, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~Border();
    void set(sf :: Vector2f base, float radius);
    sf :: Vector2f getBase() const;
    sf :: Vector2f randomPoint() const;
    float getRadius() const;
    bool check(sf :: Vector2f position) const;
    sf :: Vector2f constrains(sf :: Vector2f position) const;
    virtual void update(const float &deltaTime);
};
