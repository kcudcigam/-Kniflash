#include "EnemyController.h"
#include <iostream>
extern SignalPool signalPool;
extern std :: mt19937_64 rnd;

EnemyController :: EnemyController(const std :: vector<std :: string> &tag) : Entity(tag) {
    cx[0] = rnd() & 1, cx[1] = 1 - cx[0];
    cy[0] = rnd() & 1, cy[1] = 1 - cy[0];
    cx[0] *= (rnd() % maxn + 1), cx[1] *= (rnd() % maxn + 1);
    cy[0] *= (rnd() % maxn + 1), cy[1] *= (rnd() % maxn + 1);
    std :: uniform_real_distribution<float> d(0.1f, 0.6f);
    std :: uniform_real_distribution<float> p(0.01f, 0.05f);
    interval = d(rnd); attackProbability = p(rnd);
    auto attackTimer = new Timer(0.4f, 0, "", 0, {"attackTimer"});
    addChild(attackTimer);
    auto updateTimer = new Timer(0.1f, 0, "", 0, {"updateTimer"});
    addChild(updateTimer);
}
EnemyController :: ~EnemyController() {

}
void EnemyController :: move(sf :: Vector2f pos, bool reverse) {
    pos -= getTransform().transformPoint(0.f, 0.f);
    if(reverse) pos *= -1.f;
    cx[0] = pos.x < 0, cx[1] = 1 - cx[0];
    cy[0] = pos.y < 0, cy[1] = 1 - cy[0];
}

void EnemyController :: update(const float &deltaTime) {
    
    Entity :: update(deltaTime);

    if(!super() || signalPool.contains(0, "pause")) return;

    auto updateTimer = static_cast<Timer*>(find("updateTimer").back());
    if(!updateTimer -> isActive()) {
        updateTimer -> reset();
        auto distance = [](const sf :: Vector2f &u) {return u.x * u.x + u.y * u.y;};
        const auto pos = getTransform().transformPoint(0.f, 0.f);
        auto border = static_cast<Border*>(root() -> find("border").back());

        auto enemy = signalPool.query(uuid(), "nearest");
        if(enemy) {
            auto it = root() -> find(enemy);
            const int u = signalPool.query(super() -> uuid(), "player_health") + signalPool.query(super() -> uuid(), "player_knife");
            const int v = signalPool.query(it -> uuid(), "player_health") + signalPool.query(it -> uuid(), "player_knife");
            if(signalPool.query(super() -> uuid(), "player_knife") >= v)
                move(it -> getTransform().transformPoint(0.f, 0.f));
            if(signalPool.query(it -> uuid(), "player_knife") >= u || u <= 5)
                move(it -> getTransform().transformPoint(0.f, 0.f), true);
        }

        const float maxd = 1200.f;
        const auto knifeup = root() -> find("knifeup");
        Entity* res = nullptr;
        for(auto it : knifeup) {
            if(!static_cast<Hitbox*>(it) -> isActive() || !border -> check(it -> getTransform().transformPoint(0.f, 0.f)))
                continue;
            auto dis = distance(it -> getTransform().transformPoint(0.f, 0.f) - pos);
            if(dis > maxd * maxd) continue;
            if(!res || dis < distance(res -> getTransform().transformPoint(0.f, 0.f) - pos) )
                res = it;
        }
        //std :: cerr << knifeup.size() std :: endl;
        if(res) {
            move(res -> getTransform().transformPoint(0.f, 0.f));
        }

        const auto speedup = root() -> find("speedup");
        res = nullptr;
        for(auto it : speedup) {
            if(!static_cast<Hitbox*>(it) -> isActive() || !border -> check(it -> getTransform().transformPoint(0.f, 0.f)))
                continue;
            auto dis = distance(it -> getTransform().transformPoint(0.f, 0.f) - pos);
            if(dis > maxd * maxd) continue;
            if(!res || dis < distance(res -> getTransform().transformPoint(0.f, 0.f) - pos) )
                res = it;
        }
        if(res) {
            move(res -> getTransform().transformPoint(0.f, 0.f));
        }

        const auto healthup = root() -> find("healthup");
        res = nullptr;
        for(auto it : healthup) {
            if(!static_cast<Hitbox*>(it) -> isActive() || !border -> check(it -> getTransform().transformPoint(0.f, 0.f)))
                continue;
            auto dis = distance(it -> getTransform().transformPoint(0.f, 0.f) - pos);
            if(dis > maxd * maxd) continue;
            if(!res || distance(it -> getTransform().transformPoint(0.f, 0.f) - pos) < distance(res -> getTransform().transformPoint(0.f, 0.f) - pos) )
                res = it;
        }
        if(res && signalPool.query(super() -> uuid(), "player_health") < 5) {
            move(res -> getTransform().transformPoint(0.f, 0.f));
        }

        if(enemy) {
            auto it = root() -> find(enemy);
            const int u = signalPool.query(super() -> uuid(), "player_health") + signalPool.query(super() -> uuid(), "player_knife");
            const int v = signalPool.query(it -> uuid(), "player_health") + signalPool.query(it -> uuid(), "player_knife");
            if(signalPool.query(super() -> uuid(), "player_knife") >= v + 3) {
                move(it -> getTransform().transformPoint(0.f, 0.f));
            }

            auto timer = static_cast<Timer*>(find("attackTimer").back());
            if(!timer -> isActive()) {
                std :: uniform_real_distribution<float> p(0.f, 1.f);
                if(p(rnd) < attackProbability || signalPool.query(super() -> uuid(), "player_knife") >= v) {
                    signalPool.add(super() -> uuid(), "attack");
                    timer -> reset();
                }
            }
        }
        const auto radius = border -> getRadius() - 3.f;
        if(distance(border -> getBase() - pos) > radius * radius) {
            move(border -> getBase());
        }
        
    }
    

    delta += deltaTime;
    
    if(delta >= interval) {
        delta = 0.f;
        const int px = (cx[1] > cx[0]), py = (cy[1] > cy[0]);
        std :: uniform_real_distribution<float> d(0.f, 1.f);
        
        if(d(rnd) < std :: expintf(1.f / interval / (cx[0] + cx[1]))) {
            cx[px]++, cx[px ^ 1] = 0;
        }
        else {
            cx[px ^ 1]++; cx[px] = 0;
        }
        if(d(rnd) < std :: expintf(1.f / interval / (cy[0] + cy[1]))) {
            cy[py]++, cy[py ^ 1] = 0;
        }
        else {
            cy[py ^ 1]++; cy[py] = 0;
        }
    }
    
    if(cx[0] > cx[1]) signalPool.add(super() -> uuid(), "Moveleft");
    else signalPool.add(super() -> uuid(), "Moveright");
    if(cy[0] > cy[1]) signalPool.add(super() -> uuid(), "Moveup");
    else signalPool.add(super() -> uuid(), "Movedown");

    for(int i = 0; i <= 1; i++) {
        if(cx[i] > maxn) cx[i] = 1;
        if(cy[i] > maxn) cy[i] = 1;
    }

}