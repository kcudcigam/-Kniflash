#pragma once
#include "Frame.h"
#include "Resource.h"
#include "SignalPool.h"
#include "StaticEntity.h"
#include "Timer.h"

class KnifeCircle : public Entity {
private:
    const int maxNumber = 30;
    float velocity = 200.f, radius = 45.f, delta = 12.f;
public:
    KnifeCircle(int number = 4, const std :: vector<std :: string> &tag = {});
    virtual ~KnifeCircle();
    void setNumber(int number);
    int getNumber() const;
    void add();
    void inc();
    float getRadius() const;
    virtual void update(const float& deltaTime);
};