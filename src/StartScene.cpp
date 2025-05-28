#include "StartScene.h"
#include <iostream>
extern Resource resource;
extern SignalPool signalPool;

StartScene :: StartScene(sf :: RenderWindow* window) : Entity({}, window) {
    auto background = new StaticEntity(new sf :: Sprite(*resource.getImg("background.jpg")));
    background -> transform.scale(1.f, 1.f);
    addChild(background);

    auto border = new Border({6794.f, 5277.f}, 1200.f, 5, 0, {"border"});
    addChild(border);

    auto knifeManager = new KnifeManager({"knifeManager"});
    addChild(knifeManager);

    for(int i = 1; i <= enemyCount; i++) {
        auto enemy = new Player(border, {"player"}, false);
        enemy -> transform = sf :: Transform().translate(border -> randomPoint()); 
        auto controller = new EnemyController({"controller"});
        enemy -> addChild(controller);
        addChild(enemy);
    }

    auto bush = new Bush(border, 4, 2);
    addChild(bush);

    auto shade = new sf :: RectangleShape();
    shade -> setSize(sf :: Vector2f (static_cast<float>(getWindow() -> getSize().x), static_cast<float>(getWindow() -> getSize().y)));
    shade -> setOrigin(shade -> getSize() / 2.f);
    shade -> setPosition(border -> getBase());
    shade -> setFillColor(sf :: Color(0, 0, 0, 225));
    
    addChild(new StaticEntity(shade, 20));

    addChild(new Button(0, "game", L"开始游戏", resource.getFont("font-button.ttf"), 32, border -> getBase(), 500));
    //addChild(new Button(0, "exit", "开始游戏", resource.getFont("font-button.ttf"), 32, border -> getBase(), 50));

    const float &zoom = 1.f;
    auto position = border -> getBase();
    sf :: Vector2f center = {std :: floor(position.x + 0.5f), std :: floor(position.y + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(getWindow() -> getSize().x), static_cast<float>(getWindow() -> getSize().y)};
    auto view = sf :: View(center, size); view.zoom(zoom); getWindow() -> setView(view);

    std :: cerr << "done!" << std :: endl;
}
StartScene :: ~StartScene() {

}
void StartScene :: update(const float &deltaTime) {
    Entity :: update(deltaTime);
    /*
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard: :: Space)) {
        signalPool.add(0, "game");
    }*/
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape)) {
        signalPool.add(0, "exit");
    }
}