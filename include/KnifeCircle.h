#pragma once
#include "Frame.h"
#include "Resource.h"
#include "StaticEntity.h"

class KnifeCircle : public Entity {
private:
    float velocity = 200.f, radius = 45.f, delta = 12.f;
public:
    KnifeCircle(int number = 25);
    virtual ~KnifeCircle();
    void setNumber(int number);
    void add();
    void inc();
    float getRadius() const;
    void update(const float& deltaTime);
};