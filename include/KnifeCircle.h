#pragma once
#include "Frame.h"
#include "Resource.h"
#include "StaticEntity.h"

class KnifeCircle : public Entity {
private:
    float velocity = 200.f, radius = 80.f, delta = 15.f;
public:
    KnifeCircle(int number = 10);
    virtual ~KnifeCircle();
    void setNumber(int number);
    void add();
    void inc();
    float getRadius() const;
    void update(const float& deltaTime);
};