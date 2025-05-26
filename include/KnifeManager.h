#pragma once
#include "FlyKnife.h"

class KnifeManager : public Entity {
public:
    KnifeManager(const std :: vector<std :: string> &tag = {});
    virtual ~KnifeManager();
    virtual void update(const float& deltaTime);
};
