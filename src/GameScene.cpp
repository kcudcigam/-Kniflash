#include "GameScene.h"
#include <iostream>
extern Resource resource;
extern SignalPool signalPool; 
GameScene :: GameScene(sf :: RenderWindow* window) : Entity({}, window) {
    signalPool.clear();

    auto pic = new sf :: Sprite(*resource.getImg("background.jpg"));
    pic -> setColor(sf :: Color(255, 255, 224));
    auto background = new StaticEntity(pic);
    background -> transform.scale(1.f, 1.f);
    addChild(background);

    auto border = new Border({6794.f, 5277.f}, 4500.f, 5, 0, {"border"});
    addChild(border);

    auto knifeManager = new KnifeManager({"knifeManager"});
    addChild(knifeManager);

    auto player = new Player(border, {"player", "user"});
    auto playerController = new PlayerController({"controller"});
    player -> addChild(playerController);
    addChild(player);
    //for(int i = 1; i <= 30; i++) static_cast<KnifeCircle*>(player -> find("knifeCircle").back()) -> add();

    for(int i = 1; i <= enemyCount; i++) {
        auto enemy = new Player(border, {"player", "enemy"});
        enemy -> transform = sf :: Transform().translate(border -> randomPoint()); 
        auto controller = new EnemyController({"controller"});
        enemy -> addChild(controller);
        addChild(enemy);
    }

    auto lineDrawer = new LineDrawer({"lineDrawer"});
    addChild(lineDrawer);
    //auto area = new Hitbox(sf :: FloatRect(player -> transform.transformPoint(0.f, 0.f) + sf :: Vector2f(200.f, 200.f), sf :: Vector2f(100.f, 100.f)), "player-hitbox", "hurt", 0, {"debug"});
    //auto area_timer = new Timer(0.8f, uuid(), "area", 0, {"debug_timer"});
    //addChild(area_timer);
    //addChild(area);
    auto objects = new Objects(border, 1, 0, {});
    addChild(objects);

    auto bush = new Bush(border, 10, 2);
    addChild(bush);

    auto statistics = new Statistics({"statistics"});
    addChild(statistics);

    auto shade = new sf :: RectangleShape();
    shade -> setSize(sf :: Vector2f (static_cast<float>(getWindow() -> getSize().x) + 1000.f, static_cast<float>(getWindow() -> getSize().y) + 1000.f));
    shade -> setOrigin(shade -> getSize() / 2.f);
    shade -> setPosition(border -> getBase());
    shade -> setFillColor(sf :: Color :: Black);
    addChild(new StaticEntity(shade, 999, 0, {"shade"}));
    addChild(new Transparency(uuid(), "shadeTransparency", 255.f, 0.f, 0.8f, 0.2f, {"shadeTransparency"}));
    signalPool.add(0, "pause");

    auto miniMap = new Minimap(border, 450, {"minimap"});
    addChild(miniMap);

    resource.getSound("game.ogg") -> play();
}
GameScene :: ~GameScene() {

}
std :: tuple<int, float, std :: pair<int, int>, int> GameScene :: data() {
    auto enemies = find("enemy"); int cnt = 0;
    for(auto enemy : enemies) {
        if(static_cast<Player*>(enemy) -> isActive()) cnt++;
    }
    return {static_cast<Player*>(find("user").back()) -> getSkin(), clock, std :: make_pair(cnt + 1, enemyCount + 1), static_cast<Statistics*>(find("statistics").back()) -> query(find("user").back() -> uuid())};
}

void GameScene :: update(const float& deltaTime) {
    clock += deltaTime;
    Entity :: update(deltaTime);
    auto shade = static_cast<sf :: RectangleShape*>(static_cast<StaticEntity*>(find("shade").back()) -> get());
    shade -> setFillColor(sf :: Color(shade -> getFillColor().r, shade -> getFillColor().g, shade -> getFillColor().b, signalPool.query(uuid(), "shadeTransparency")));


    if(!static_cast<Transparency*>(find("shadeTransparency").back()) -> isActive()) {
        signalPool.del(0, "pause");
    }

    Player* player = static_cast<Player*>(find("user").back());
    auto enemies = find("enemy"); int cnt = 0;
    for(auto enemy : enemies) {
        if(static_cast<Player*>(enemy) -> isActive()) cnt++;
    }
    if((!player -> isActive() || !cnt) && !signalPool.contains(uuid(), "end")) {
        signalPool.add(uuid(), "end");
        player -> hide();
        static_cast<Minimap*>(find("minimap").back()) -> hide();
        const auto tmp = data();
        auto end = new EndScene(getWindow(), std :: get<0>(tmp), std :: get<1>(tmp), std :: get<2>(tmp), std :: get<3>(tmp));
        end -> transform = sf :: Transform().translate(player -> transform.transformPoint(0.f, 0.f));
        addChild(end);
    }
    const int border = 4500;
    const int survive = cnt + 1, all = enemyCount + 1;
    if(survive * 2 <= all) {
        signalPool.add(0, "border", border / 2);
    }
    if(survive * 5 <= all) {
        signalPool.add(0, "border", border / 3);
    }
    if(survive * 15 <= all) {
        signalPool.add(0, "border", border / 4);
    }
    if(survive * 20 <= all) {
        signalPool.add(0, "border", border / 5);
    }
    //std :: cerr << static_cast<Statistics*>(find("statistics").back()) -> query(find("user").back() -> uuid()) << std :: endl;
    /*
    if(!signalPool.contains(uuid(), "area")) {
        static_cast<Timer*>(find("debug_timer").back()) -> reset();
        static_cast<Hitbox*>(find("debug").back()) -> reset();
    }   */
    //const auto originView = window -> getView();
    //window -> setView(sf :: View());
    const float &zoom = 1.f;
    auto position = player -> getTransform().transformPoint(0.f, 0.f);
    sf :: Vector2f center = {std :: floor(position.x + 0.5f), std :: floor(position.y + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(getWindow() -> getSize().x), static_cast<float>(getWindow() -> getSize().y)};
    auto view = sf :: View(center, size); view.zoom(zoom); getWindow() -> setView(view);
}