#include "Timer.h"
extern SignalPool signalPool;
Timer :: Timer(float duration, uint64_t receiver, const std :: string &signal, int content, const std :: vector<std :: string> &tag)
: Entity(tag), duration(duration), receiver(receiver), signal(signal), content(content) {
    currentTime = 0.f;
}
Timer :: ~Timer() {

}
void Timer :: reset() {
    currentTime = duration;
    signalPool.add(receiver, signal, content);
}
bool Timer :: isActive() const {
    return !(currentTime <= 0.f);
}
void Timer :: update(const float &deltaTime) {
    if(!isActive()) return;
    currentTime -= deltaTime;
    if(!isActive()) {
        signalPool.del(receiver, signal);
    }
    Entity :: update(deltaTime);
}
