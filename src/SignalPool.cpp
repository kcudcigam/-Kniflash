#include "SignalPool.h"

void SignalPool :: add(int receiver, const std :: string &signal, int content) {
    pool[receiver][signal] = content;
}
bool SignalPool :: contains(int owner, const std :: string &signal) const {
    return pool.contains(owner) && pool.at(owner).contains(signal);
}
void SignalPool :: del(int owner, const std :: string &signal) {
    if(pool[owner].contains(signal)) {
        pool[owner].erase(signal);
    }
}
int SignalPool :: query(int owner, const std :: string &signal) const {
    if(!contains(owner, signal)) return -1;
    return pool.at(owner).at(signal);
}
