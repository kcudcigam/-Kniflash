#include "Objects.h"
extern Resource resource;
extern SignalPool signalPool;

Objects :: Objects(const Border* border, int layer, int order, const std :: vector<std :: string> &tag)
: Entity(tag), border(border), layer(layer), order(order) {
    

    const auto  knifeImg = combineFrame(resource.getImg("props.png"), { 2, 40}, { 2, 40}, {64, 64}, {32.f, 32.f}).back();
    const auto  speedImg = combineFrame(resource.getImg("props.png"), { 6, 38}, { 6, 38}, {64, 64}, {32.f, 32.f}).back();
    const auto healthImg = combineFrame(resource.getImg("props.png"), {10, 37}, {10, 37}, {64, 64}, {32.f, 32.f}).back();

    for(int i = 1; i <= knifeNumber; i++) {
        auto hitbox = new Hitbox(sf :: FloatRect({-64.f, -64.f}, {128.f, 128.f}), "player-hitbox", "knifeup");
        set(hitbox);
        auto img = new sf :: Sprite; knifeImg.load(img);
        auto obj = new StaticEntity(img, 1); obj -> transform.scale(2.f, 2.f);
        auto timer = new Timer(10.f, hitbox -> uuid(), "loading", 0, {"timer"});
        addChild(hitbox); hitbox -> addChild(obj); hitbox -> addChild(timer);
    }

    for(int i = 1; i <= speedNumber; i++) {
        auto hitbox = new Hitbox(sf :: FloatRect({-64.f, -64.f}, {128.f, 128.f}), "player-hitbox", "speedup");
        set(hitbox);
        auto img = new sf :: Sprite; speedImg.load(img);
        auto obj = new StaticEntity(img, 1); obj -> transform.scale(2.f, 2.f);
        auto timer = new Timer(10.f, hitbox -> uuid(), "loading", 0, {"timer"});
        addChild(hitbox); hitbox -> addChild(obj); hitbox -> addChild(timer);
    }

    for(int i = 1; i <= healthNumber; i++) {
        auto hitbox = new Hitbox(sf :: FloatRect({-64.f, -64.f}, {128.f, 128.f}), "player-hitbox", "healthup");
        set(hitbox);
        auto img = new sf :: Sprite; healthImg.load(img);
        auto obj = new StaticEntity(img, 1); obj -> transform.scale(2.f, 2.f);
        auto timer = new Timer(10.f, hitbox -> uuid(), "loading", 0, {"timer"});
        addChild(hitbox); hitbox -> addChild(obj); hitbox -> addChild(timer);
    }

}
Objects :: ~Objects() {

}
bool Objects :: check(sf :: Vector2f position) const {
    auto distance = [](const sf :: Vector2f &d) {return d.x * d.x + d.y * d.y;};
    for(auto child : components) {
        if(static_cast<Hitbox*>(child) -> isActive() && distance(position - child -> transform.transformPoint(0.f, 0.f)) < minimalDistance * minimalDistance) {
            return false;
        }
    }
    return true;
}
void Objects :: set(Entity* obj) const {
    obj -> transform = sf :: Transform().translate(border -> randomPoint());
    while(!check(obj -> transform.transformPoint(0.f, 0.f))) {
        obj -> transform = sf :: Transform().translate(border -> randomPoint());
    }
}

void Objects :: update(const float &deltaTime) {
    Entity :: update(deltaTime);
    for(auto child : components) {
        auto it = static_cast<Hitbox*>(child);
        if(!it -> isActive()) {
            if(!signalPool.contains(it -> uuid(), "countdown")) {
                signalPool.add(it -> uuid(), "countdown");
                static_cast<Timer*>(it -> find("timer").back()) -> reset();
            }
            else if(!signalPool.contains(it -> uuid(), "loading")) {
                it -> transform = sf :: Transform().translate(border -> randomPoint());
                set(it); it -> reset();
                signalPool.del(it -> uuid(), "countdown");
            }
            else {
                static_cast<Timer*>(it -> find("timer").back()) -> update(deltaTime);
            }
        }
    }
}