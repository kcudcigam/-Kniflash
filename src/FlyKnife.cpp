#include "FlyKnife.h"
extern Resource resource;
extern SignalPool signalPool;

FlyKnife :: FlyKnife(uint64_t owner, const sf :: Vector2f &pos, const sf :: Vector2f &v, const std :: vector<std :: string> &tag)
 : owner(owner), Entity(tag), pos(pos), v(v) {
    
    auto sprite = new sf :: Sprite();
    combineFrame(resource.getImg("props.png"), {10, 9}, {10, 9}, {64, 64}, {0.f, 64.f}).back().load(sprite);
    auto knife = new StaticEntity(sprite, 1, 2);

    knife -> transform.rotate(45.f);
    addChild(knife);

    transform.translate(pos);
    transform.rotate(atan2f(v.y, v.x) * 180.f / acosf(-1.f), -delta, 0.f);
}
FlyKnife :: ~FlyKnife() {
    
}
bool FlyKnife :: isActive() const {
    return delta < maxd;
}
void FlyKnife :: update(const float &deltaTime) {
    if(!isActive()) return;
    delta += deltaTime * velocity;
    transform = sf :: Transform().translate(pos);
    transform.translate(delta, 0.f);
    transform.rotate(atan2f(v.y, v.x) * 180.f / acosf(-1.f), -delta, 0.f);
    auto players = root() -> find("player");
    auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
    const float range = 80.f;
    for(auto player : players) {
        auto dis = distance(player -> getTransform().transformPoint(0.f, 0.f) - getTransform().transformPoint(0.f, 0.f));
        if(dis < range * range) {
            signalPool.add(player -> uuid(), "hurt", owner);
            delta = maxd; break;
        }
    }
    Entity :: update(deltaTime);
}