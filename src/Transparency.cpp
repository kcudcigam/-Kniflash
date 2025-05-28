#include "Transparency.h"
extern SignalPool signalPool;

Transparency :: Transparency(uint64_t receiver, const std :: string &signal, float start, float end, float duration, float delay, const std :: vector<std :: string> & tag)
: Entity(tag), receiver(receiver), signal(signal), current(start), target(end), duration(duration), delay(delay) {
    if(duration <= 0.f) velocity = 1e9;
    else velocity = (end - start) / duration;
    signalPool.add(receiver, signal, int(start + 0.5));
}
Transparency :: ~Transparency() {

}
bool Transparency :: isActive() const {
    const float eps = 1e-6;
    return fabsf(target - current) < eps;
}
void Transparency :: update(const float &deltaTime) {
    Entity :: update(deltaTime);
    if(delay > 0.f) {
        delay -= deltaTime;
        return;
    }
    current += velocity * deltaTime;
    if(velocity < 0.f) current = std :: max(current, target);
    else current = std :: min(current, target);
    signalPool.add(receiver, signal, int(current + 0.5));
}