#include "Border.h"
extern std :: mt19937_64 rnd;
extern SignalPool signalPool;

Border :: Border(sf :: Vector2f base, float radius, int layer, int order, const std :: vector<std :: string> &tag)
: Entity(tag), base(base), radius(radius), layer(layer), order(order) {
    set(base, radius);
}
Border :: ~Border() {

}
void Border :: set(sf :: Vector2f base, float radius) {
    for(auto child : components) {
        delete child;
    }
    components.clear();
    this -> base = base;
    this -> radius = radius;
    auto circle = new sf :: CircleShape(radius + 55.f, 80);
    circle -> setPosition(base - sf :: Vector2f(circle -> getRadius(), circle -> getRadius()));
    circle -> setFillColor(sf :: Color :: Transparent);
    circle -> setOutlineThickness(5000.f);
    circle -> setOutlineColor(sf :: Color(0, 0, 0, 180));
    addChild(new StaticEntity(circle, layer, order));
}
sf :: Vector2f Border :: getBase() const {
    return getTransform().transformPoint(base);
}
float Border :: getRadius() const {
    return radius;
}

sf :: Vector2f Border :: randomPoint() const {
    std :: uniform_real_distribution<float> d(-radius, radius);
    sf :: Vector2f point = {d(rnd), d(rnd)};
    auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
    while(distance(point) > radius * radius) {
        point = {d(rnd), d(rnd)};
    }
    return point + getBase();
}
bool Border :: check(sf :: Vector2f position) const {
    auto distance = [](sf :: Vector2f d) {return d.x * d.x + d.y * d.y;};
    auto offset = base - position;
    return !(distance(offset) > radius * radius);
}
sf :: Vector2f Border :: constrains(sf :: Vector2f position) const {
    if(check(position)) {
        return sf :: Vector2f(0.f, 0.f);
    }
    auto distance = [](sf :: Vector2f d) {return d.x * d.x + d.y * d.y;};
    auto offset = base - position;
    return offset - offset / sqrtf(distance(offset)) * (radius - 2.f);
}
void Border :: update(const float &deltaTime) {
    if(signalPool.contains(0, "border") && signalPool.query(0, "border") < radius) {
        set(getBase(), std :: max(static_cast<float>(signalPool.query(0, "border")), radius - velocity * deltaTime));
    }
    Entity :: update(deltaTime);
}