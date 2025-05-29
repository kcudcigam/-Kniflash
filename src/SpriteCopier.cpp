#include "SpriteCopier.h"

SpriteCopier :: SpriteCopier(sf :: Sprite* sprite, int maxNumber, float interval, float velocity, int layer, int order, const std :: vector<std :: string> &tags)
: Entity(tags), sprite(sprite), maxNumber(maxNumber), interval(interval), velocity(velocity), layer(layer), order(order) {

}
SpriteCopier :: ~SpriteCopier() {

}
void SpriteCopier :: set(bool active) {
    this -> active = active;
}
void SpriteCopier :: update(const float& deltaTime) {
    if(!active) {
        for(auto it : components) delete it;
        components.clear();
        return;
    
    }
    for(auto child : components) {
        auto it = static_cast<sf :: Sprite*>(static_cast<StaticEntity*>(child) -> get());
        float transparency = std :: max(0.f, it -> getColor().a - deltaTime * velocity);
        it -> setColor(sf :: Color(it -> getColor().r, it -> getColor().g, it -> getColor().b, static_cast<int>(transparency + 0.5f)));
    }
    current -= deltaTime;
    if(current <= 0.f) {
        auto copy = new sf :: Sprite(*sprite);
        auto child = new StaticEntity(copy, layer, order, {}, false);
        child -> transform = getTransform();
        addChild(child);
        current = interval;
    }
    if(components.size() > maxNumber) {
        delete *components.begin();
        components.erase(components.begin());
    }
    Entity :: update(deltaTime);
}