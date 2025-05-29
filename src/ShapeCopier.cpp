#include "ShapeCopier.h"

ShapeCopier :: ShapeCopier(sf :: Shape* shape, int maxNumber, float interval, float velocity, int layer, int order, const std :: vector<std :: string> &tags)
: Entity(tags), shape(shape), maxNumber(maxNumber), interval(interval), velocity(velocity), layer(layer), order(order) {

}
ShapeCopier :: ~ShapeCopier() {

}
void ShapeCopier :: set(bool active) {
    this -> active = active;
}
void ShapeCopier :: update(const float& deltaTime) {
    if(!active) {
        for(auto it : components) delete it;
        components.clear();
        return;
    }
    for(auto child : components) {
        auto it = static_cast<EllipseShape*>(static_cast<StaticEntity*>(child) -> get());
        float transparency = std :: max(0.f, it -> getFillColor().a - deltaTime * velocity);
        it -> setFillColor(sf :: Color(it -> getFillColor().r, it -> getFillColor().g, it -> getFillColor().b, static_cast<int>(transparency + 0.5f)));
    }
    current -= deltaTime;
    if(current <= 0.f) {
        auto copy = new EllipseShape(*static_cast<EllipseShape*>(shape));
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