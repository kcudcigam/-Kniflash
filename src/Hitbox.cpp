#include "Hitbox.h"
extern SignalPool signalPool;

Hitbox :: Hitbox(sf :: FloatRect rect, const std :: string &target, const std :: string &signal, int content, const std :: vector<std :: string> &tag)
: RectEntity(rect, tag), target(target), signal(signal), content(content) {

}
Hitbox :: ~Hitbox() {

}
void Hitbox :: reset() {
    active = true;
}
bool Hitbox :: isActive() const {
    return active;
}
void Hitbox :: update(const float &deltaTime) {
    if(!active) return;
    RectEntity :: update(deltaTime);
    
    auto list = root() -> find(target);
    const auto rect = getGlobalRect();
    for(auto it : list) {
        auto obj = static_cast<RectEntity*>(it);
        if(rect.intersects(obj -> getGlobalRect())) {
            signalPool.add(obj -> uuid(), signal, content);
            active = false;
            break;
        }
    }
    
}