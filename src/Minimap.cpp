#include "Minimap.h"
extern SignalPool signalPool;

Minimap :: Minimap(const Border* border, int size, const std :: vector<std :: string> & tag)
: Entity(tag), border(border), size(size) {
    radius = border -> getRadius(); 
}
Minimap :: ~Minimap() {

}
#include <iostream>
void Minimap :: update(const float &deltaTime) {
    for(auto child : components) delete child;
    components.clear();
    auto position = root() -> find("user").back() -> getTransform().transformPoint(0.f, 0.f);
    position -= sf :: Vector2f (static_cast<float>(root() -> getWindow() -> getSize().x), static_cast<float>(root() -> getWindow() -> getSize().y)) / 2.f;
    transform = sf :: Transform().translate(position);

    auto rect = new sf :: RectangleShape(sf :: Vector2f(size, size));
    rect -> setFillColor(sf :: Color(150, 150, 150));
    addChild(new StaticEntity(rect, 500, 0));
    
    const float r = (size / 2.f) * border -> getRadius() / radius;
    float t = radius;
    if(signalPool.contains(0, "border")) {
        t = signalPool.query(0, "border");
    }
    t = (size / 2.f) * t / radius;
    
    auto bounds = new sf :: CircleShape(r, 60);
    bounds -> setOrigin(r, r);
    bounds -> setPosition(size / 2.f, size / 2.f);
    addChild(new StaticEntity(bounds, 500, 1));
    
    auto target = new sf :: CircleShape(t, 60);
    target -> setOrigin(t, t);
    target -> setPosition(size / 2.f, size / 2.f);
    target -> setFillColor(sf :: Color :: Transparent);
    target -> setOutlineThickness(4.f);
    target -> setOutlineColor(sf :: Color :: Yellow);
    addChild(new StaticEntity(target, 500, 2));
    auto players = root() -> find("player");
    auto user = root() -> find("user").back() -> uuid();
    for(auto player : players) {
        if(!static_cast<Player*>(player) -> isActive()) continue;
        auto it = new sf :: RectangleShape(sf :: Vector2f(d, d));
        
        if(player -> uuid() == user) it -> setFillColor(sf :: Color :: Green);
        else it -> setFillColor(sf :: Color :: Red);
        auto pos = (player -> getTransform().transformPoint(0.f, 0.f) - border -> getBase()) * (size / (2 * radius));
        pos += sf :: Vector2f(size / 2.f, size / 2.f);
        it -> setPosition(pos);
        addChild(new StaticEntity(it, 500, 4));
    }
    Entity :: update(deltaTime);
}
