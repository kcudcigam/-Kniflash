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
    if(!super() || signalPool.contains(0, "pause")) return;
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left))
        signalPool.add(super() -> uuid(), "Moveleft");
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right))
        signalPool.add(super() -> uuid(), "Moveright");
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up))
        signalPool.add(super() -> uuid(), "Moveup");
     if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down))
        signalPool.add(super() -> uuid(), "Movedown");
    auto target = root() -> find(signalPool.query(uuid(), "nearest"));
    if(target) {
        signalPool.add(target -> uuid(), "targeted");
        const auto start = getTransform().transformPoint(0.f, 0.f), end =  target -> getTransform().transformPoint(0.f, 0.f);
        auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
        const float d = 790.f;
        static_cast<LineDrawer*>(root() -> find("lineDrawer").back()) -> draw(getTransform().transformPoint(0.f, 30.f), target -> getTransform().transformPoint(0.f, 30.f), 25.f, 0, 10);
        auto timer = static_cast<Timer*>(find("timer").back());
        if(distance(start - end) < d * d && sf :: Mouse :: isButtonPressed(sf :: Mouse :: Button :: Left) && !timer -> isActive()) {
            signalPool.add(super() -> uuid(), "attack", target -> uuid());
            timer -> reset();
        }
    }
}