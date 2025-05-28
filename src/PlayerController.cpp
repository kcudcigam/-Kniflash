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
        auto timer = static_cast<Timer*>(find("timer").back());
        if(sf :: Mouse :: isButtonPressed(sf :: Mouse :: Button :: Left) && !timer -> isActive()) {
            signalPool.add(super() -> uuid(), "attack", target -> uuid());
            timer -> reset();
        }
    }
}