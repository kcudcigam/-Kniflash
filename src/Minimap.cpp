#include "Minimap.h"
extern SignalPool signalPool;
extern Resource resource;

Minimap :: Minimap(const Border* border, int size, const std :: vector<std :: string> & tag)
: Entity(tag), border(border), size(size) {
    radius = border -> getRadius(); 
    circleSize = size * 0.4f;
}
Minimap :: ~Minimap() {

}
void Minimap :: hide() {
    active = false;
}
#include <iostream>
void Minimap :: update(const float &deltaTime) {
    for(auto child : components) delete child;
    components.clear();
    if(!active) return;
    auto position = root() -> find("user").back() -> getTransform().transformPoint(0.f, 0.f);
    position -= sf :: Vector2f (static_cast<float>(root() -> getWindow() -> getSize().x), static_cast<float>(root() -> getWindow() -> getSize().y)) / 2.f;
    transform = sf :: Transform().translate(position);

    auto players = root() -> find("player");
    int cnt = 0;
    for(auto player : players) {
        if(static_cast<Player*>(player) -> isActive()) cnt++;
    }
    auto character = new sf :: Text(L"SURVIVE : " + std :: to_wstring(cnt), *resource.getFont("font-title.ttf"), 36);
    const sf::FloatRect &textRect = character -> getLocalBounds();
    character -> setOrigin(textRect.left + textRect.width / 2.f, textRect.top  + textRect.height / 2.f);
    character -> setOutlineColor(sf :: Color :: Black);
    character -> setOutlineThickness(3.f);
    character -> setPosition(size / 2.f + 10.f, size + 12.f);
    addChild(new StaticEntity(character, 500));
    
    const float r = circleSize;
    //circleSize * border -> getRadius() / radius;
    float t = border -> getRadius() * circleSize / radius;
    
    auto background = new sf :: CircleShape(r, 100);
    background -> setOrigin(r, r);
    background -> setPosition(size / 2.f, size / 2.f);
    background -> setFillColor(sf :: Color :: Transparent);
    background -> setOutlineThickness(8.f);
    background -> setOutlineColor(sf :: Color(255, 255, 224));
    addChild(new StaticEntity(background, 500, -1));

    auto outline = new sf :: CircleShape(r + 8, 100);
    outline -> setOrigin(r + 8, r + 8);
    outline -> setPosition(size / 2.f, size / 2.f);
    outline -> setFillColor(sf :: Color :: Transparent);
    outline -> setOutlineThickness(2.f);
    outline -> setOutlineColor(sf :: Color :: Black);
    addChild(new StaticEntity(outline, 500, 0));

    auto bounds = new sf :: CircleShape(r, 100);
    bounds -> setOrigin(r, r);
    bounds -> setPosition(size / 2.f, size / 2.f);
    bounds -> setFillColor(sf :: Color(0, 0, 0, 220));
    bounds -> setOutlineThickness(2.f);
    bounds -> setOutlineColor(sf :: Color :: Black);
    addChild(new StaticEntity(bounds, 500, 1));
    
    auto target = new sf :: CircleShape(t, 100);
    target -> setOrigin(t, t);
    target -> setPosition(size / 2.f, size / 2.f);
    target -> setFillColor(sf :: Color :: Transparent);
    //target -> setOutlineThickness(bounds -> getRadius() - target -> getRadius());
    //target -> setOutlineColor(sf :: Color(0, 0, 0, 220));
    target -> setOutlineThickness(2.f);
    target -> setOutlineColor(sf :: Color(255, 255, 224));
    addChild(new StaticEntity(target, 500, 2));

    auto user = root() -> find("user").back() -> uuid();
    for(auto player : players) {
        if(!static_cast<Player*>(player) -> isActive()) continue;
        auto it = new sf :: RectangleShape(sf :: Vector2f(d, d));
        it -> setOrigin(d / 2, d / 2);
        if(player -> uuid() == user) it -> setFillColor(sf :: Color :: Green);
        else it -> setFillColor(sf :: Color :: Red);
        auto pos = (player -> getTransform().transformPoint(0.f, 0.f) - border -> getBase()) * (circleSize / radius);
        pos += sf :: Vector2f(size / 2.f, size / 2.f);
        it -> setPosition(pos);
        addChild(new StaticEntity(it, 500, 4));
    }
    Entity :: update(deltaTime);
}
