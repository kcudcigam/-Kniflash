#include "Player.h"
extern Resource resource;
extern SignalPool signalPool;
extern std :: mt19937_64 rnd;
Player :: Player(const Border* border, const std :: vector<std :: string> &tag, bool interactive) : Entity(tag), border(border), interactive(interactive) {
    if(border) {
        transform.translate(border -> getBase());
    }

    auto character = new DynamicEntity(1, 0, {"animation"});
    character -> transform.scale(5.f, 5.f);
    skin = rnd() % 18 + 1;
    const std :: string &img = "Character " + std :: to_string(skin) + ".png";
    character -> add("idle", Animation(combineFrame(resource.getImg(img), {0, 0}, {3, 0}, {64, 64}, {32.f, 32.f}), 0.1f));
    character -> add("walk", Animation(combineFrame(resource.getImg(img), {0, 2}, {5, 2}, {64, 64}, {32.f, 32.f}), 0.06f));
    character -> add("hurt", Animation(combineFrame(resource.getImg(img), {0, 5}, {3, 5}, {64, 64}, {32.f, 32.f}), 0.05f, false));
    character -> add("dead", Animation(combineFrame(resource.getImg(img), {0, 6}, {9, 6}, {64, 64}, {32.f, 32.f}), 0.1f, false));
    addChild(character);

    auto copy = new SpriteCopier(character -> get(), 12, 0.004, 5000.f, 1, -1, {"copy"});
    copy -> set(false);
    character -> addChild(copy);


    auto targetCircle = new sf :: Sprite(*resource.getImg("circle.png"));
    targetCircle -> setOrigin(100.f, 100.f);
    targetCircle -> setColor(sf :: Color(255, 0, 0, 180));
    auto target = new StaticEntity(targetCircle, 1, 1, {"target"});
    target -> transform.scale(0.8f, 0.8f);
    target -> transform.translate(0.f, 10.f);
    target -> addChild(new Rotater(360.f));
    target -> setStatus(false);
    addChild(target);

    if(interactive) {
        auto healthBar = new HealthBar(uuid(), 3, 0, {"healthbar"});
        healthBar -> transform.translate(-5.f, -100.f).scale(4.f, 5.f);
        addChild(healthBar);
        signalPool.add(uuid(), "player_health", healthBar -> getNumber());

        auto killNumber = new KillNumber(3, 0, {"killNumber"});
        killNumber -> transform.translate(-60.f, -175.f).scale(1.f, 1.f);
        addChild(killNumber);
    }

    auto knifeCircle = new KnifeCircle(4, {"knifeCircle"});
    addChild(knifeCircle);
    signalPool.add(uuid(), "player_knife", knifeCircle -> getNumber());

    auto box = new RectEntity(sf :: FloatRect(-64.f, -64.f, 128.f, 128.f), {"player-hitbox"});
    addChild(box);

    auto speedUp = new Timer(3.f, uuid(), "Inspeedup", 0, {"speedup"});
    addChild(speedUp);

    auto regen = new DynamicEntity(1, 5, {"regen"});
    regen -> add("animation", Animation(combineFrame(resource.getImg("regen.png"), {0, 0}, {7, 0}, {96, 96}, {48.f, 48.f}), 0.08f, false));    
    regen -> transform.translate(0.f, -15.f);
    regen -> transform.scale(3.f, 3.f);
    addChild(regen);

    auto shadeShape = new EllipseShape(sf :: Vector2f(42.f, 24.f));
    shadeShape -> setFillColor(sf :: Color(0.f, 0.f, 0.f, 160.f));
    auto shade = new StaticEntity(shadeShape, 0, 100, {"playerShade"});
    shade -> transform.translate(-42.f, 50.f);
    addChild(shade);

    auto shadeCopy = new ShapeCopier(shadeShape, 10, 0.01, 2000.f, 1, -1, {"shadeCopy"});
    shadeCopy -> set(false);
    shade -> addChild(shadeCopy);

    auto hurtTimer = new Timer(0.2f, 0, "", 0, {"hurtTimer"});
    addChild(hurtTimer);

    auto soundPlayer = new SoundPlayer("user", {"sound"});
    addChild(soundPlayer);

    auto footstepTimer = new Timer(0.3f, 0, "", 0, {"footstep"});
    addChild(footstepTimer);
    //
}
Player :: ~Player() {

}
int Player :: getSkin() const {
    return skin;
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

uint64_t Player :: nearest() {
    auto players = root() -> find("player");
    std :: vector<Entity*> enemies;
    for(auto player : players)
        if(player -> uuid() != this -> uuid() && !static_cast<Player*>(player) -> isDead()) enemies.emplace_back(player);
    if(enemies.empty() || !static_cast<KnifeCircle*>(find("knifeCircle").back()) -> getNumber()) return 0;
    auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
    auto target = enemies.back(); enemies.pop_back();
    for(auto enemy : enemies) {
        const auto x = distance(enemy -> getTransform().transformPoint(0.f, 0.f) - getTransform().transformPoint(0.f, 0.f));
        const auto y = distance(target -> getTransform().transformPoint(0.f, 0.f) - getTransform().transformPoint(0.f, 0.f));
        if(x < y) target = enemy;
    }
    const float r = static_cast<KnifeCircle*>(find("knifeCircle").back()) -> getRadius() + 10.f, d = 800.f;
    auto dis = distance(target -> getTransform().transformPoint(0.f, 0.f) - getTransform().transformPoint(0.f, 0.f));
    if(dis > r * r && dis < d * d) return target -> uuid();
    return 0;
}

bool Player :: isActive() const {
    return active;
}
bool Player :: isDead() const {
    return dead;
}
void Player :: attack(const sf :: Vector2f &u) {
    auto d = u - getTransform().transformPoint(0.f, 0.f);
    if(d.x * d.x + d.y * d.y == 0.f) return;
    d /= std :: sqrt(d.x * d.x + d.y * d.y);
    auto knifeCircle = static_cast<KnifeCircle*>(find("knifeCircle").back());
    if(knifeCircle -> getNumber()) {
        root() -> find("knifeManager").back() -> addChild(new FlyKnife(uuid(), knifeCircle -> getRadius() * d + getTransform().transformPoint(0.f, 0.f), d, 1, 2));
        knifeCircle -> inc();
        static_cast<SoundPlayer*>(find("sound").back()) -> play("attack.wav");
    }
}
void Player :: combat() {
    auto players = root() -> find("player");
    std :: vector<Entity*> enemies;
    for(auto player : players)
        if(player -> uuid() != this -> uuid() && !static_cast<Player*>(player) -> isDead()) enemies.emplace_back(player);
    auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
    const float r = static_cast<KnifeCircle*>(find("knifeCircle").back()) -> getRadius() + 10.f;
    for(auto enemy : enemies) {
        const auto x = distance(enemy -> getTransform().transformPoint(0.f, 0.f) - getTransform().transformPoint(0.f, 0.f));
        if(x < r * r) {
            signalPool.add(enemy -> uuid(), "combat", uuid());
        }
    }
}
void Player :: hide() {
    active = false;
}
void Player :: hurt() {
    if(static_cast<KnifeCircle*>(find("knifeCircle").back()) -> getNumber()) {
        static_cast<KnifeCircle*>(find("knifeCircle").back()) -> inc();
        static_cast<SoundPlayer*>(find("sound").back()) -> play("defend.wav");
    }
    else {
        static_cast<HealthBar*>(find("healthbar").back()) -> inc();
        static_cast<SoundPlayer*>(find("sound").back()) -> play("hit.wav");
    }
    static_cast<DynamicEntity*>(find("animation").back()) -> play("hurt", true);
}

void Player :: update(const float& deltaTime) {
    
    if(!isActive()) return;

    if(interactive) {
        if(signalPool.contains(uuid(), "dead")) {
            if(!signalPool.contains(uuid(), "kill")) {
                signalPool.add(uuid(), "kill");
                signalPool.add(attacker, "upgrade");
                static_cast<Statistics*>(root() -> find("statistics").back()) -> add(attacker);
                static_cast<SoundPlayer*>(find("sound").back()) -> play("dead.wav");
            }
            static_cast<DynamicEntity*>(find("animation").back()) -> play("dead", true);
            dead = true;
            //find("healthbar").back() -> update(deltaTime);
            find("animation").back() -> update(deltaTime);
            if(static_cast<DynamicEntity*>(find("animation").back()) -> getAnimation("dead") -> end()) {
                active = false;
            }
            //Entity :: update(deltaTime);
            return;
        }
        if(signalPool.contains(uuid(), "upgrade")) {
            signalPool.del(uuid(), "upgrade");
            static_cast<SoundPlayer*>(find("sound").back()) -> play("add.wav");
            for(int i = 1; i <= 8; i++) static_cast<KnifeCircle*>(find("knifeCircle").back()) -> add();
        }

        static_cast<KillNumber*>(find("killNumber").back()) -> set(static_cast<Statistics*>(root() -> find("statistics").back()) -> query(uuid()));
        combat();

        if(signalPool.contains(find("player-hitbox").back() -> uuid(), "speedup")) {
            signalPool.del(find("player-hitbox").back() -> uuid(), "speedup");
            static_cast<Timer*>(find("speedup").back()) -> reset();
            //static_cast<DynamicEntity*>(find("speedCircle").back()) -> play("animation");
            static_cast<SpriteCopier*>(find("copy").back()) -> set(true);
            static_cast<ShapeCopier*>(find("shadeCopy").back()) -> set(true);
            static_cast<SoundPlayer*>(find("sound").back()) -> play("speedup.wav");
            //static_cast<StaticEntity*>(find("playerShade").back()) -> setStatus(false);
        }
        if(!signalPool.contains(uuid(), "Inspeedup")) {
            //static_cast<DynamicEntity*>(find("speedCircle").back()) -> play("");
            static_cast<SpriteCopier*>(find("copy").back()) -> set(false);
            static_cast<ShapeCopier*>(find("shadeCopy").back()) -> set(false);
            //static_cast<StaticEntity*>(find("playerShade").back()) -> setStatus(true);
        }
        if(signalPool.contains(uuid(), "targeted")) {
            static_cast<StaticEntity*>(find("target").back()) -> setStatus(true);
            signalPool.del(uuid(), "targeted");
        }
        else {
            static_cast<StaticEntity*>(find("target").back()) -> setStatus(false);
        }
        
        if(signalPool.contains(uuid(), "hurt")) {
            hurt(); attacker = signalPool.query(uuid(), "hurt");
            signalPool.del(uuid(), "hurt");
        }

        if(signalPool.contains(uuid(), "combat")) {
            auto timer = static_cast<Timer*>(find("hurtTimer").back());
            if(!timer -> isActive()) {
                hurt(); attacker = signalPool.query(uuid(), "combat");
                signalPool.add(attacker, "hurt", uuid());
                timer -> reset();
            }
            signalPool.del(uuid(), "combat");
        }
        
        if(signalPool.contains(find("player-hitbox").back() -> uuid(), "knifeup")) {
            signalPool.del(find("player-hitbox").back() -> uuid(), "knifeup");
            static_cast<KnifeCircle*>(find("knifeCircle").back()) -> add();
            static_cast<SoundPlayer*>(find("sound").back()) -> play("add.wav");
        }
        if(signalPool.contains(find("player-hitbox").back() -> uuid(), "healthup")) {
            signalPool.del(find("player-hitbox").back() -> uuid(), "healthup");
            static_cast<HealthBar*>(find("healthbar").back()) -> recover();
            static_cast<DynamicEntity*>(find("regen").back()) -> reset();
            static_cast<DynamicEntity*>(find("regen").back()) -> play("animation");
            static_cast<SoundPlayer*>(find("sound").back()) -> play("regen.wav");
        }
        signalPool.add(uuid(), "player_health", static_cast<HealthBar*>(find("healthbar").back()) -> getNumber());
    }

    signalPool.add(find("controller").back() -> uuid(), "nearest", nearest());
    if(signalPool.contains(uuid(), "attack")) {
        auto enemy = root() -> find(nearest());
        if(enemy) attack(enemy -> transform.transformPoint(0.f, 0.f));
        signalPool.del(uuid(), "attack");
    }
    signalPool.add(uuid(), "player_knife", static_cast<KnifeCircle*>(find("knifeCircle").back()) -> getNumber());
    
    if(!direction) {
        auto reverse = sf :: Transform(); reverse.scale(-1.f, 1.f);
        find("animation").back() -> transform.combine(reverse);
    }
    float vx = 0.f, vy = 0.f; bool flag = false;
    if(signalPool.contains(uuid(), "Moveup")) {
        vy -= 1.f; signalPool.del(uuid(), "Moveup"); flag = true;
    }
    if(signalPool.contains(uuid(), "Movedown")) {
        vy += 1.f; signalPool.del(uuid(), "Movedown"); flag = true;
    }
    if(signalPool.contains(uuid(), "Moveleft")) {
        vx -= 1.f; signalPool.del(uuid(), "Moveleft"); flag = true;
    }
    if(signalPool.contains(uuid(), "Moveright")) {
        vx += 1.f; signalPool.del(uuid(), "Moveright"); flag = true;
    }
    if(flag && !static_cast<Timer*>(find("footstep").back()) -> isActive()) {
        static_cast<Timer*>(find("footstep").back()) -> reset();
        static_cast<SoundPlayer*>(find("sound").back()) -> play("step.wav");
    }
    if(vx != 0.f || vy != 0.f) {
        const float v = sqrtf(vx * vx + vy * vy);
        move(vx / v, vy / v, deltaTime);
    }
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
    Entity :: update(deltaTime);
}