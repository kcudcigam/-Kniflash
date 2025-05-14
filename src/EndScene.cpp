#include "EndScene.h"
extern Resource resource;
extern SignalPool signalPool; 
EndScene :: EndScene(sf :: RenderTarget* window) : Entity(), window(window) {
    auto background = new StaticEntity(new sf :: Sprite(*resource.getImg("end-background.png")));
    background -> transform.scale(1.f, 1.f);
    addChild(background);
    window -> setView(window -> getDefaultView());
}
EndScene :: ~EndScene() {

}
void EndScene :: update(const float& deltaTime) {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter)) {
        signalPool.add(0, "start");
    }
    Entity :: update(deltaTime);
    
}