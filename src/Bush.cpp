#include "Bush.h"
extern Resource resource;

Bush :: Bush(const Border* border, int number, int layer, int order, const std :: vector<std :: string> &tag)
: Entity(tag), border(border), number(number), layer(layer), order(order) {
    set(number);
}
Bush :: ~Bush() {

}
bool Bush :: check(sf :: Vector2f position) const {
    auto distance = [](const sf :: Vector2f &d) {return d.x * d.x + d.y * d.y;};
    for(auto child : components) {
        if(distance(position - child -> transform.transformPoint(0.f, 0.f)) < minimalDistance * minimalDistance) {
            return false;
        }
    }
    return true;
}
void Bush :: set(int number) {
    for(auto child : components) {
        delete child;
    }
    components.clear();
    this -> number = number;
    
    for(int i = 1; i <= number; i++) {
        auto bush = new sf :: Sprite(*resource.getImg("bush.png"));
        bush -> setOrigin(16.f, 16.f);
        bush -> scale(15.f, 15.f);
        auto child = new StaticEntity(bush, layer, order);
        child -> transform = sf :: Transform().translate(border -> randomPoint());
        while(!check(child -> transform.transformPoint(0.f, 0.f))) {
            child -> transform = sf :: Transform().translate(border -> randomPoint());
        }
        addChild(child);
    }
}