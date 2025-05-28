#include "EndScene.h"
extern Resource resource;
extern SignalPool signalPool;

#include <iostream>

EndScene :: EndScene(int skin, float clock, std :: pair<int, int> rank, int kills) : Entity() {
    //auto background = new StaticEntity(new sf :: Sprite(*resource.getImg("end-background.png")));
    //background -> transform.scale(1.f, 1.f);
    //addChild(background);
    //window -> setView(window -> getDefaultView());
    auto shade = new sf :: RectangleShape();
    auto window = root() -> getWindow();
    shade -> setSize(sf :: Vector2f (static_cast<float>(root() -> getWindow() -> getSize().x), static_cast<float>(root() -> getWindow() -> getSize().y)));
    shade -> setOrigin(shade -> getSize() / 2.f);
    //shade -> setPosition(border -> getBase());
    shade -> setFillColor(sf :: Color(0, 0, 0, 225));
    
    addChild(new StaticEntity(shade, 20));

    std :: cerr << skin << ' ' << clock << ' ' << rank.first << '/' << rank.second << ' ' << kills << std :: endl;
}
EndScene :: ~EndScene() {

}
void EndScene :: update(const float& deltaTime) {
    Entity :: update(deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter)) {
        signalPool.add(0, "start");
    }
}