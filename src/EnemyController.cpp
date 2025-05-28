#include "EnemyController.h"
extern SignalPool signalPool;
extern std :: mt19937_64 rnd;

EnemyController :: EnemyController(const std :: vector<std :: string> &tag) : Entity(tag) {
    cx[0] = rnd() & 1, cx[1] = 1 - cx[0];
    cy[0] = rnd() & 1, cy[1] = 1 - cy[0];
    cx[0] *= (rnd() % 10 + 1), cx[1] *= (rnd() % 10 + 1);
    cy[0] *= (rnd() % 10 + 1), cy[1] *= (rnd() % 10 + 1);
    std :: uniform_real_distribution<float> d(0.1f, 0.6f);
    interval = d(rnd);
    auto timer = new Timer(0.5f, 0, "", 0, {"timer"});
    addChild(timer);
}
EnemyController :: ~EnemyController() {

}

void EnemyController :: update(const float &deltaTime) {
    
    Entity :: update(deltaTime);

    if(!super() || signalPool.contains(0, "pause")) return;

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

    const uint64_t maxn = 10;
    for(int i = 0; i <= 1; i++) {
        if(cx[i] > maxn) cx[i] = 1;
        if(cy[i] > maxn) cy[i] = 1;
    }
    auto enemy = signalPool.query(uuid(), "nearest");
    if(!enemy) {
        target = 0; return;
    }
    auto timer = static_cast<Timer*>(find("timer").back());
    if(enemy != target) timer -> reset();
    target = enemy;
    
    if(!timer -> isActive()) {
        signalPool.add(super() -> uuid(), "attack");
        timer -> reset();
    }

}