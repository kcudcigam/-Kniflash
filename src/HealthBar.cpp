#include "HealthBar.h"
extern Resource resource;
extern SignalPool signalPool;

sf :: Sprite* createImg(int health) {
    auto img = combineFrame(resource.getImg("healthbar.png"), {6 - health, 11}, {6 - health, 11}, {48, 16}, {24, 8}).back();
    auto sprite = new sf :: Sprite; img.load(sprite);
    return sprite;
}
HealthBar :: HealthBar(uint64_t owner, int layer, int order, const std :: vector<std :: string> &tag)
: Entity(tag), owner(owner), layer(layer), order(order) {
    auto bar = new StaticEntity(createImg(health), layer, order);
    addChild(bar);
}
HealthBar :: ~HealthBar() {

}
void HealthBar :: add() {
    if(health >= maxHealth) return;
    health++;
    static_cast<StaticEntity*>(components.back()) -> set(createImg(health));
}
void HealthBar :: inc() {
    if(health <= 0) return;
    health--;
    static_cast<StaticEntity*>(components.back()) -> set(createImg(health));
}
void HealthBar :: recover() {
    health = maxHealth;;
    static_cast<StaticEntity*>(components.back()) -> set(createImg(health));
}
void HealthBar :: update(const float &deltaTime) {
    if(health <= 0) {
        signalPool.add(owner, "dead");
    }
    Entity :: update(deltaTime);
}