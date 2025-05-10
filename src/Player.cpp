#include "Player.h"
extern Resource resource;


Player :: Player() : Entity({"player"}) {
    transform.translate(3500.f, 2000.f);

    auto character = new DynamicEntity(1, 0, {"animation"});
    character -> transform.scale(5.f, 5.f);
    character -> add("idle", Animation(combineFrame(resource.getImg("Character 1.png"), {0, 0}, {3, 0}, {64, 64}, {32.f, 32.f}), 0.1f));
    character -> add("walk", Animation(combineFrame(resource.getImg("Character 1.png"), {0, 2}, {5, 2}, {64, 64}, {32.f, 32.f}), 0.06f));
    addChild(character);

    auto knifeCircle = new KnifeCircle();
    addChild(knifeCircle);
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
}

void Player :: update(const float& deltaTime) {
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

    const float &d = std :: sqrt(velocity.x * velocity.x + velocity.y * velocity.y) / maxVelocity;
    if(d > 1.f) velocity /= d;  
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

    for(auto child : opponents)
        child -> update(deltaTime);
}