#include "GameScene.h"
extern Resource resource;


GameScene :: GameScene(sf :: RenderTarget* window) : Entity(), window(window) {
    auto background = new StaticEntity(new sf :: Sprite(*resource.getImg("background.jpg")));
    background -> transform.scale(1.f, 1.f);
    addChild(background);
    auto player = new Player();
    addChild(player);
}
GameScene :: ~GameScene() {

}
void GameScene :: update(const float& deltaTime) {
    for(auto child : opponents)
        child -> update(deltaTime);
    //const auto originView = window -> getView();
    window -> setView(sf :: View());
    const float &zoom = 1.f;
    auto player = find("player").back();
    auto position = player -> getTransform().transformPoint(0.f, 0.f);
    sf :: Vector2f center = {std :: floor(position.x + 0.5f), std :: floor(position.y + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(window -> getSize().x), static_cast<float>(window -> getSize().y)};
    auto view = sf :: View(center, size); view.zoom(zoom); window -> setView(view);
    
}