#pragma once
#include "Frame.h"
#include "Resource.h"
#include "StaticEntity.h"

class KillNumber : public Entity {
private:
    int layer, order;
    int kill = 0;
public:
    KillNumber(int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~KillNumber();
    void set(int number);
};