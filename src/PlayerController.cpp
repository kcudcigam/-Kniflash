#include "PlayerController.h"
extern SignalPool signalPool;

PlayerController :: PlayerController(const std :: vector<std :: string> &tag) : Entity(tag) {
    auto timer = new Timer(0.2f, 0, "", 0, {"timer"});
    addChild(timer);
}
PlayerController :: ~PlayerController() {

}
void PlayerController :: update(const float &deltaTime) {
    Entity :: update(deltaTime);
    if(!super()) return;
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left))
        signalPool.add(super() -> uuid(), "Moveleft");
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right))
        signalPool.add(super() -> uuid(), "Moveright");
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up))
        signalPool.add(super() -> uuid(), "Moveup");
     if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down))
        signalPool.add(super() -> uuid(), "Movedown");
    auto enemies = root() -> find("enemy");
    if(enemies.empty()) return;
    for(auto enemy : enemies) {
        signalPool.del(enemy -> uuid(), "targeted");
    }
    const float d = 700.f, r = 100.f;
    auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
    auto target = enemies.back(); enemies.pop_back();
    for(auto enemy : enemies) {
        const auto x = distance(enemy -> getTransform().transformPoint(0.f, 0.f) - super() -> getTransform().transformPoint(0.f, 0.f));
        const auto y = distance(target -> getTransform().transformPoint(0.f, 0.f) - super() -> getTransform().transformPoint(0.f, 0.f));
        if(x < y) target = enemy;
    }
    auto dis = distance(target -> getTransform().transformPoint(0.f, 0.f) - super() -> getTransform().transformPoint(0.f, 0.f));
    if(dis < d * d && dis > r * r) {
        signalPool.add(target -> uuid(), "targeted");
        auto timer = static_cast<Timer*>(find("timer").back());
        if(sf :: Mouse :: isButtonPressed(sf :: Mouse :: Button :: Left) && !timer -> isActive()) {
            signalPool.add(super() -> uuid(), "attack", target -> uuid());
            timer -> reset();
        }
    }
}