#include "GameScene.h"
extern Resource resource;


GameScene :: GameScene(sf :: RenderTarget* window) : Entity(), window(window) {
    auto background = new StaticEntity(new sf :: Sprite(*resource.getImg("background.jpg")));
    background -> transform.scale(1.f, 1.f);
    addChild(background);

    auto player = new Player();
    addChild(player);

    auto circle = new sf :: CircleShape(player -> radius + 55.f, 80);
    circle -> setPosition(player -> base - sf :: Vector2f(circle -> getRadius(), circle -> getRadius()));
    circle -> setFillColor(sf :: Color :: Transparent);
    circle -> setOutlineThickness(2000.f);
    circle -> setOutlineColor(sf :: Color(0, 0, 0, 180));
    auto border = new StaticEntity(circle, 0, 1);
    addChild(border);

    auto speedArea = new Hitbox(sf :: FloatRect(player -> transform.transformPoint(0.f, 0.f) + sf :: Vector2f(200.f, 200.f), sf :: Vector2f(100.f, 100.f)), "hitbox", "speedup");
    addChild(speedArea);
}
GameScene :: ~GameScene() {

}
void GameScene :: update(const float& deltaTime) {
    Entity :: update(deltaTime);
    //const auto originView = window -> getView();
    window -> setView(sf :: View());
    const float &zoom = 1.f;
    auto player = find("player").back();
    auto position = player -> getTransform().transformPoint(0.f, 0.f);
    sf :: Vector2f center = {std :: floor(position.x + 0.5f), std :: floor(position.y + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(window -> getSize().x), static_cast<float>(window -> getSize().y)};
    auto view = sf :: View(center, size); view.zoom(zoom); window -> setView(view);
    
}