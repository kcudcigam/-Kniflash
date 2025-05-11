#pragma once
#include "SFML/Graphics.hpp"

class SignalPool {
private:
    std :: map<int, std :: map<std :: string, int> > pool;
public:
    void add(int receiver, const std :: string &signal, int content = 0);
    bool contains(int owner, const std :: string &signal) const;
    void del(int owner, const std :: string &signal);
    int query(int owner, const std :: string &signal) const;
};
