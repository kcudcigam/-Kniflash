#include "Objects.h"
extern Resource resource;
extern SignalPool signalPool;

Objects :: Objects(const Border* border, int layer, int order, const std :: vector<std :: string> &tag)
: Entity(tag), border(border), layer(layer), order(order) {
    

    const auto knifeImg = combineFrame(resource.getImg("props.png"), {9, 10}, {9, 10}, {64, 64}, {32.f, 32.f}).back();
    const auto speedImg = combineFrame(resource.getImg("props.png"), {9, 11}, {9, 11}, {64, 64}, {32.f, 32.f}).back();
    for(int i = 1; i <= knifeNumber; i++) {
        auto hitbox = new Hitbox(sf :: FloatRect({-64.f, -64.f}, {128.f, 128.f}), "player-hitbox", "knifeup");
        hitbox -> transform = sf :: Transform().translate(border -> randomPoint());
        auto img = new sf :: Sprite; knifeImg.load(img);
        auto obj = new StaticEntity(img, 1); obj -> transform.scale(2.f, 2.f);
        auto timer = new Timer(10.f, hitbox -> uuid(), "loading", 0, {"timer"});
        addChild(hitbox); hitbox -> addChild(obj); hitbox -> addChild(timer);
    }

    for(int i = 1; i <= speedNumber; i++) {
        auto hitbox = new Hitbox(sf :: FloatRect({-64.f, -64.f}, {128.f, 128.f}), "player-hitbox", "speedup");
        hitbox -> transform = sf :: Transform().translate(border -> randomPoint());
        auto img = new sf :: Sprite; speedImg.load(img);
        auto obj = new StaticEntity(img, 1); obj -> transform.scale(2.f, 2.f);
        auto timer = new Timer(10.f, hitbox -> uuid(), "loading", 0, {"timer"});
        addChild(hitbox); hitbox -> addChild(obj); hitbox -> addChild(timer);
    }

}
Objects :: ~Objects() {

}
void Objects :: update(const float &deltaTime) {
    for(auto child : components) {
        auto it = static_cast<Hitbox*>(child);
        if(!it -> isActive()) {
            if(!signalPool.contains(it -> uuid(), "countdown")) {
                signalPool.add(it -> uuid(), "countdown");
                static_cast<Timer*>(it -> find("timer").back()) -> reset();
            }
            else if(!signalPool.contains(it -> uuid(), "loading")) {
                it -> transform = sf :: Transform().translate(border -> randomPoint()); it -> reset();
                signalPool.del(it -> uuid(), "countdown");
            }
            else {
                static_cast<Timer*>(it -> find("timer").back()) -> update(deltaTime);
            }
        }
    }
    Entity :: update(deltaTime);
}