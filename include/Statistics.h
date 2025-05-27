#pragma once
#include "Entity.h"
#include "SignalPool.h"
#include "Timer.h"

class Statistics : public Entity {
private:
    std :: map<uint64_t, int> kills;
public:
    Statistics(const std :: vector<std :: string> &tag = {});
    virtual ~Statistics();
    void add(uint64_t uuid);
    int query(uint64_t uuid);
};
