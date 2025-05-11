#pragma once
#include "SFML/Graphics.hpp"

class SignalPool {
private:
    std :: map<uint64_t, std :: map<std :: string, int> > pool;
public:
    void add(uint64_t receiver, const std :: string &signal, int content = 0);
    bool contains(uint64_t owner, const std :: string &signal) const;
    void del(uint64_t owner, const std :: string &signal);
    int query(uint64_t owner, const std :: string &signal) const;
};
