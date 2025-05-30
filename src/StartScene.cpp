#include "StartScene.h"
#include <iostream>
extern Resource resource;
extern SignalPool signalPool;

StartScene :: StartScene(sf :: RenderWindow* window) : Entity({}, window) {
    signalPool.clear();

    auto pic = new sf :: Sprite(*resource.getImg("background.jpg"));
    pic -> setColor(sf :: Color(255, 255, 224));
    auto background = new StaticEntity(pic);
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
    shade -> setSize(sf :: Vector2f (static_cast<float>(getWindow() -> getSize().x) + 2.f, static_cast<float>(getWindow() -> getSize().y) + 2.f));
    shade -> setOrigin(shade -> getSize() / 2.f);
    shade -> setPosition(border -> getBase());
    shade -> setFillColor(sf :: Color :: Black);
    
    addChild(new StaticEntity(shade, 20, 0, {"shade"}));

    auto text = new sf :: Text(L"Kniflash", *resource.getFont("font-title.ttf"), 256);

    const sf::FloatRect &textRect = text -> getLocalBounds();
    text -> setOrigin(textRect.left + textRect.width / 2.f, textRect.top  + textRect.height / 2.f);
    auto title = new StaticEntity(text, 500, 0, {"title"});
    title -> transform.translate(border -> getBase() + sf :: Vector2f(0.f, -100.f));
    addChild(title);
    addChild(new Button(0, "game", L"开始游戏", resource.getFont("font-button.ttf"), 64, border -> getBase() + sf :: Vector2f(0.f, 250.f), 500, 0, {"gameButton"}));
    addChild(new Button(0, "exit", L"退出游戏", resource.getFont("font-button.ttf"), 64, border -> getBase() + sf :: Vector2f(0.f, 400.f), 500, 0, {"exitButton"}));

    addChild(new Transparency(uuid(), "shadeTransparency", 255.f, 225.f, 0.5));
    addChild(new Transparency(uuid(), "titleTransparency", 0.f, 255.f, 0.8));
    addChild(new Transparency(uuid(), "gameTransparency", 0.f, 255.f, 0.5, 0.8));
    addChild(new Transparency(uuid(), "exitTransparency", 0.f, 255.f, 0.5, 1.2));

    const float &zoom = 1.f;
    auto position = border -> getBase();
    sf :: Vector2f center = {std :: floor(position.x + 0.5f), std :: floor(position.y + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(getWindow() -> getSize().x), static_cast<float>(getWindow() -> getSize().y)};
    auto view = sf :: View(center, size); view.zoom(zoom); getWindow() -> setView(view);

    resource.getSound("start.ogg") -> play();
}
StartScene :: ~StartScene() {
    resource.getSound("start.ogg") -> stop();
}
void StartScene :: update(const float &deltaTime) {
    Entity :: update(deltaTime);
    auto shade = static_cast<sf :: RectangleShape*>(static_cast<StaticEntity*>(find("shade").back()) -> get());
    shade -> setFillColor(sf :: Color(shade -> getFillColor().r, shade -> getFillColor().g, shade -> getFillColor().b, signalPool.query(uuid(), "shadeTransparency")));
    auto title = static_cast<sf :: Text*>(static_cast<StaticEntity*>(find("title").back()) -> get());
    title -> setFillColor(sf :: Color(title -> getFillColor().r, title -> getFillColor().g, title -> getFillColor().b, signalPool.query(uuid(), "titleTransparency")));
    auto game = static_cast<Button*>(find("gameButton").back()) -> get();
    game -> setFillColor(sf :: Color(game -> getFillColor().r, game -> getFillColor().g, game -> getFillColor().b, signalPool.query(uuid(), "gameTransparency")));
    auto exit = static_cast<Button*>(find("exitButton").back()) -> get();
    exit -> setFillColor(sf :: Color(exit -> getFillColor().r, exit -> getFillColor().g, exit -> getFillColor().b, signalPool.query(uuid(), "exitTransparency")));
}   