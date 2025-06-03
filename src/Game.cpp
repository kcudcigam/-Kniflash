#include "Game.h"
extern Resource resource;
extern RenderPool renderPool;
extern SignalPool signalPool;

std::atomic<bool> atomic_bool(false);
void loading() {
    resource.loadFrom("../resource");
    atomic_bool.store(true);
}

//Game
Game :: Game() : height(1280), width(1920), window(sf :: VideoMode(width, height), " GAME Kniflash") {
    sf :: Image icon; icon.loadFromFile("../resource/image/icon/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.clear();
    
    sf :: Texture loadingTexture;
    loadingTexture.loadFromFile("../resource/image/icon/load.png");
    auto animation = combineFrame(&loadingTexture, {0, 0}, {29, 0}, {200, 200}, {100.f, 100.f});
    sf :: Sprite sprite; sprite.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);
    const float duration = 0.03;

    std :: thread load(loading); load.detach();
    sf :: Clock loadingClock; float delta = 0.f;
    while(!atomic_bool && window.isOpen()) {
        if(window.getSize() != sf :: Vector2u(width, height)) window.setSize(sf :: Vector2u(width, height));
        delta += loadingClock.restart().asSeconds();
        window.clear();
        animation[int(delta / duration) % 30].load(&sprite);
        window.draw(sprite);
        window.display();
        
        while(window.pollEvent(event)) {
            if(event.type == sf :: Event :: Closed) window.close();
        }
    }
    if(window.isOpen()) {
        scene = new StartScene(&window);
    }
    
}
Game :: ~Game() {
    if(scene) delete scene;
    scene = nullptr;
}

void Game :: update() {
    
    if(window.getSize() != sf :: Vector2u(width, height)) window.setSize(sf :: Vector2u(width, height));
    
    while(window.pollEvent(event)) {
        if(event.type == sf :: Event :: Closed) window.close();
    }
    deltaTime = clock.restart().asSeconds();
    if(signalPool.contains(0, "exit")) {
        signalPool.del(0, "exit");
        window.close();
        return;
    }
    if(signalPool.contains(0, "start")) {
        delete scene;
        scene = new StartScene(&window);
    }
    if(signalPool.contains(0, "game")) {
        delete scene;
        scene = new GameScene(&window);
    }

    if(scene) {
        scene -> update(deltaTime);
    }
}
void Game :: render() {
    if(!window.isOpen()) return;
    window.clear();
    renderPool.render(&window);
    window.display();

}
void Game :: run() {
    deltaTime = clock.restart().asSeconds();
    while (window.isOpen()) update(), render();
}
