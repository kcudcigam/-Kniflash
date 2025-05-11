#include "GameScene.h"
extern Resource resource;
GameScene :: GameScene(sf :: RenderTarget* window) : Entity(), window(window) {
    auto background = new StaticEntity(new sf :: Sprite(*resource.getImg("background.jpg")));
    background -> transform.scale(1.f, 1.f);
    addChild(background);

    auto border = new Border({6794.f, 5277.f}, 4500.f, 0, 1, {"border"});
    addChild(border);

    auto player = new Player(border, {"player", "user"});
    addChild(player);

    auto area = new Hitbox(sf :: FloatRect(player -> transform.transformPoint(0.f, 0.f) + sf :: Vector2f(200.f, 200.f), sf :: Vector2f(100.f, 100.f)), "player-hitbox", "knifedown", 0, {"debug"});
    addChild(area);

    auto objects = new Objects(border, 1, 0, {});
    addChild(objects);
}
GameScene :: ~GameScene() {

}
void GameScene :: update(const float& deltaTime) {
    Entity :: update(deltaTime);
    static_cast<Hitbox*>(find("debug").back()) -> reset();
    //const auto originView = window -> getView();
    //window -> setView(sf :: View());
    const float &zoom = 1.f;
    auto player = find("user").back();
    auto position = player -> getTransform().transformPoint(0.f, 0.f);
    sf :: Vector2f center = {std :: floor(position.x + 0.5f), std :: floor(position.y + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(window -> getSize().x), static_cast<float>(window -> getSize().y)};
    auto view = sf :: View(center, size); view.zoom(zoom); window -> setView(view);
    
}