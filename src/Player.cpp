#include "Player.h"
extern Resource resource;
extern SignalPool signalPool;
extern std :: mt19937_64 rnd;
#include <iostream>
Player :: Player(const Border* border, const std :: vector<std :: string> &tag) : Entity(tag), border(border) {
    if(border) {
        transform.translate(border -> getBase());
    }
    auto character = new DynamicEntity(1, 0, {"animation"});
    character -> transform.scale(5.f, 5.f);
    const std :: string &img = "Character " + std :: to_string(rnd() % 18 + 1) + ".png";
    character -> add("idle", Animation(combineFrame(resource.getImg(img), {0, 0}, {3, 0}, {64, 64}, {32.f, 32.f}), 0.1f));
    character -> add("walk", Animation(combineFrame(resource.getImg(img), {0, 2}, {5, 2}, {64, 64}, {32.f, 32.f}), 0.06f));
    character -> add("hurt", Animation(combineFrame(resource.getImg(img), {0, 5}, {3, 5}, {64, 64}, {32.f, 32.f}), 0.05f, false));
    character -> add("dead", Animation(combineFrame(resource.getImg(img), {0, 6}, {9, 6}, {64, 64}, {32.f, 32.f}), 0.1f, false));
    addChild(character);

    auto healthBar = new HealthBar(uuid(), 3, 0, {"healthbar"});
    healthBar -> transform.translate(-5.f, -110.f).scale(4.f, 5.f);
    addChild(healthBar);

    auto knifeCircle = new KnifeCircle(4, {"knifeCircle"});
    addChild(knifeCircle);

    auto box = new RectEntity(sf :: FloatRect(-64.f, -64.f, 128.f, 128.f), {"player-hitbox"});
    addChild(box);

    auto speedUp = new Timer(3.f, uuid(), "Inspeedup", 0, {"speedup"});
    addChild(speedUp);

    auto circle = new DynamicEntity(0, 2, {"speedCircle"});
    circle -> add("animation", Animation(combineFrame(resource.getImg("effect.png"), {0, 2}, {4, 2}, {96, 96}, {48.f, 48.f}), 0.05f));    
    circle -> transform.translate(0.f, 40.f);
    circle -> transform.scale(2.5f, 2.5f);
    addChild(circle);
    //
}
Player :: ~Player() {

}
void Player :: move(const float &x, const float &y, const float &deltaTime) {
    auto limit = [](float &u, float &v, const float &maxVelocity) {
        u = std :: min(u,  maxVelocity); u = std :: max(u, -maxVelocity);
        const float &w = std :: sqrt(maxVelocity * maxVelocity - u * u);
        v = std :: min(v, w); v = std :: max(v, -w);
    };
    if(x != 0) direction = (x > 0);
    velocity.x += acceleration * x * deltaTime;
    velocity.y += acceleration * y * deltaTime;
    const float &d = std :: sqrt(velocity.x * velocity.x + velocity.y * velocity.y) / maxVelocity;
    if(d > 1.f) velocity /= d;  
}
void Player :: update(const float& deltaTime) {
    if(signalPool.contains(uuid(), "dead")) {
        static_cast<DynamicEntity*>(find("animation").back()) -> play("dead", true);
        //find("healthbar").back() -> update(deltaTime);
        find("animation").back() -> update(deltaTime);
        if(static_cast<DynamicEntity*>(find("animation").back()) -> getAnimation("dead") -> end()) {
            signalPool.add(0, "end");
        }
        //Entity :: update(deltaTime);
        return;
    }
    if(signalPool.contains(find("player-hitbox").back() -> uuid(), "speedup")) {
        signalPool.del(find("player-hitbox").back() -> uuid(), "speedup");
        static_cast<Timer*>(find("speedup").back()) -> reset();
        static_cast<DynamicEntity*>(find("speedCircle").back()) -> play("animation");
    }
    if(!signalPool.contains(uuid(), "Inspeedup")) {
        static_cast<DynamicEntity*>(find("speedCircle").back()) -> play("");
    }
    if(signalPool.contains(find("player-hitbox").back() -> uuid(), "knifeup")) {
        signalPool.del(find("player-hitbox").back() -> uuid(), "knifeup");
        static_cast<KnifeCircle*>(find("knifeCircle").back()) -> add();
    }
    if(signalPool.contains(find("player-hitbox").back() -> uuid(), "healthup")) {
        signalPool.del(find("player-hitbox").back() -> uuid(), "healthup");
        static_cast<HealthBar*>(find("healthbar").back()) -> recover();
    }
    if(signalPool.contains(find("player-hitbox").back() -> uuid(), "hurt")) {
        signalPool.del(find("player-hitbox").back() -> uuid(), "hurt");
        if(static_cast<KnifeCircle*>(find("knifeCircle").back()) -> getNumber()) {
            static_cast<KnifeCircle*>(find("knifeCircle").back()) -> inc();
        }
        else {
            static_cast<HealthBar*>(find("healthbar").back()) -> inc();
        }
        static_cast<DynamicEntity*>(find("animation").back()) -> play("hurt", true);
    }

    if(!direction) {
        auto reverse = sf :: Transform(); reverse.scale(-1.f, 1.f);
        find("animation").back() -> transform.combine(reverse);
    }
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left))
        move(-1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right))
       move(1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up))
        move(0.f, -1.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down))
        move(0.f,  1.f, deltaTime);

    auto updateSpeed = [&deltaTime](float &x, const float &deceleration) {
        const int u = (x > 0.f ? 1 : x < 0.f ? -1 : 0); x *= u;
        x -= deltaTime * deceleration; x = std :: max(x, 0.f) * u;
    };
    updateSpeed(velocity.x, deceleration);
    updateSpeed(velocity.y, deceleration);

    transform.translate(velocity * deltaTime);
   
    
    
    if(!direction) {
        auto reverse = sf :: Transform(); reverse.scale(-1.f, 1.f);
        find("animation").back() -> transform.combine(reverse);
    }
    if(velocity != sf :: Vector2f(0.f, 0.f)) {
        static_cast<DynamicEntity*>(find("animation").back()) -> play("walk");
    }
    else {
        static_cast<DynamicEntity*>(find("animation").back()) -> play("idle");
    }

    if(signalPool.contains(uuid(), "Inspeedup")) {
        transform.translate(velocity * (deltaTime * 1.f));
    }
    

    if(border) {
        transform.translate(border -> constrains(getTransform().transformPoint(0.f, 0.f)));
    }
    
    for(auto child : components)
        child -> update(deltaTime);
}