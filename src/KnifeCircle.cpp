#include "KnifeCircle.h"
extern Resource resource;
extern RenderPool renderPool;

KnifeCircle :: KnifeCircle(int number) {
    setNumber(number);
    //transform.rotate(-pii / 4);
    //transform.rotate(100.f);
}
KnifeCircle :: ~KnifeCircle() {

}
void KnifeCircle :: setNumber(int number) {
    for(auto child : opponents) delete child;
    opponents.clear();
    const auto img = combineFrame(resource.getImg("props.png"), {10, 9}, {10, 9}, {64, 64}, {0.f, 64.f}).back();
    
    sf :: Transform position; position.translate(radius + number * delta, 0.f);

    for(int i = 0; i < number; i++) {
        
        auto sprite = new sf :: Sprite;
        img.load(sprite);

        auto knife = new StaticEntity(sprite, 1);
        
        knife -> transform = position;
        position.rotate(360.f / number, - radius - number * delta, 0.f);
        addChild(knife);
    }
}
void KnifeCircle :: add() {
    setNumber(opponents.size() + 1);
}
void KnifeCircle :: inc() {
    if(!opponents.empty()) setNumber(opponents.size() - 1);
}
float KnifeCircle :: getRadius() const {
    return radius + opponents.size() * delta;
}
void KnifeCircle :: update(const float& deltaTime) {
    auto tmp = getTransform().transformPoint(0.f, 0.f);
    //std :: cerr << tmp.x << ' ' << tmp.y << ' ' << std :: endl;
    for(auto child : opponents) {
        child -> transform.rotate(velocity * deltaTime, -getRadius(), 0.f);
        child -> transform.rotate(45.f);
    }
    for(auto child : opponents)
        child -> update(deltaTime);
    for(auto child : opponents) {
        child -> transform.rotate(-45.f);
    }
}
