#include "SignalPool.h"

void SignalPool :: add(uint64_t receiver, const std :: string &signal, uint64_t content) {
    pool[receiver][signal] = content;
}
bool SignalPool :: contains(uint64_t owner, const std :: string &signal) const {
    return pool.contains(owner) && pool.at(owner).contains(signal);
}
void SignalPool :: del(uint64_t owner, const std :: string &signal) {
    if(pool[owner].contains(signal)) {
        pool[owner].erase(signal);
    }
}
uint64_t SignalPool :: query(uint64_t owner, const std :: string &signal) const {
    if(!contains(owner, signal)) return -1;
    return pool.at(owner).at(signal);
}
