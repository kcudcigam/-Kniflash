#include "EndScene.h"
extern Resource resource;
extern SignalPool signalPool;

#include <iostream>

EndScene :: EndScene(sf :: RenderTarget* window, int skin, float clock, std :: pair<int, int> rank, int kills) : Entity(), window(window) {
    auto background = new StaticEntity(new sf :: Sprite(*resource.getImg("end-background.png")));
    background -> transform.scale(1.f, 1.f);
    addChild(background);
    window -> setView(window -> getDefaultView());
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