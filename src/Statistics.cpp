#include "Statistics.h"

Statistics :: Statistics(const std :: vector<std :: string> &tag) : Entity(tag) {

}
Statistics :: ~Statistics() {

}
void Statistics :: add(uint64_t uuid) {
    kills[uuid]++;
}
int Statistics :: query(uint64_t uuid) {
    return kills[uuid];
}
