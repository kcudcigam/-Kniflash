#include "KnifeCircle.h"
extern Resource resource;
extern SignalPool signalPool;
extern RenderPool renderPool;

KnifeCircle :: KnifeCircle(int number, const std :: vector<std :: string> &tag) : Entity(tag) {
    auto loading = new Timer(1.f, uuid(), "loading", 0, {"loading"});
    addChild(loading);
    setNumber(number);
}
KnifeCircle :: ~KnifeCircle() {

}
void KnifeCircle :: setNumber(int number) {
    while(components.back() -> contains("knife")) {
        delete components.back();
        components.pop_back();
    }
    const auto img = combineFrame(resource.getImg("props.png"), {10, 9}, {10, 9}, {64, 64}, {0.f, 64.f}).back();
    
    sf :: Transform position; position.translate(radius + number * delta, 0.f);

    for(int i = 0; i < number; i++) {
        
        auto sprite = new sf :: Sprite;
        img.load(sprite);

        auto knife = new StaticEntity(sprite, 1, 0, {"knife"});
        
        knife -> transform = position;
        position.rotate(360.f / number, - radius - number * delta, 0.f);
        addChild(knife);
    }
}
int KnifeCircle :: getNumber() const{
    return static_cast<int>(components.size()) - 1;
}
void KnifeCircle :: add() {
    if(getNumber() < maxNumber) {
        setNumber(getNumber() + 1);
        static_cast<Timer*>(find("loading").back()) -> reset();
    }
}
void KnifeCircle :: inc() {
    if(getNumber()) {
        setNumber(getNumber() - 1);
        static_cast<Timer*>(find("loading").back()) -> reset();
    }
}
float KnifeCircle :: getRadius() const {
    return radius + getNumber() * delta;
}
void KnifeCircle :: update(const float& deltaTime) {
    
    if(getNumber() < 4 && !signalPool.contains(uuid(), "loading")) add();

    for(auto child : components) {
        child -> transform.rotate(velocity * deltaTime, -getRadius(), 0.f);
        child -> transform.rotate(45.f);
    }
    Entity :: update(deltaTime);
    for(auto child : components) {
        child -> transform.rotate(-45.f);
    }
}
