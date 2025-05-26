#pragma once
#include "SFML/Graphics.hpp"

class SignalPool {
private:
    std :: map<uint64_t, std :: map<std :: string, uint64_t> > pool;
public:
    void add(uint64_t receiver, const std :: string &signal, uint64_t content = 0);
    bool contains(uint64_t owner, const std :: string &signal) const;
    void del(uint64_t owner, const std :: string &signal);
    uint64_t query(uint64_t owner, const std :: string &signal) const;
};
