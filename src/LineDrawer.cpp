#include "LineDrawer.h"

LineDrawer :: LineDrawer(const std :: vector<std :: string> &tag) : Entity(tag) {

}
LineDrawer :: ~LineDrawer() {
    for(auto it : rub) delete it;
}
void LineDrawer :: draw(const sf :: Vector2f &start, const sf :: Vector2f &end, float delta, int layer, int order) {
    auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
    const int cnt = std :: sqrt(distance(start - end)) / delta + 0.5;
    if(!cnt) return;
    const auto d = (end - start) / static_cast<float>(cnt);
    auto x = start;
    for(int i = 0; i <= cnt; i++) {
        auto circle = new sf :: CircleShape(radius); circle -> setFillColor(sf :: Color(255, 0, 0, 200));
        auto child = new StaticEntity(circle, layer, order); child -> transform.translate(x);
        addChild(child);
        x += d;
    }
}
void LineDrawer :: update(const float &deltaTime) {
    Entity :: update(deltaTime);
    for(auto it : rub) delete it;
    rub.clear(); swap(components, rub);
}