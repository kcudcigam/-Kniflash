#include "Game.h"
#include <iostream>
extern Resource resource;
extern RenderPool renderPool;
//Game
Game :: Game() : height(1280), width(1920), window(sf :: VideoMode(width, height), " Kniflash") {
    sf :: Image icon; icon.loadFromFile("../resource/image/icon/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.clear();

    sf :: RectangleShape background;
    sf :: Texture loadingTexture;
    loadingTexture.loadFromFile("../resource/image/background/loading-background.png");
    background.setSize({width, height});
    background.setTexture(&loadingTexture);
    window.draw(background);
    window.display();
    
    resource.loadFrom("../resource");

    scene = new GameScene(&window);
}
Game :: ~Game() {
    if(scene) delete scene;
    scene = nullptr;
}

void Game :: update() {
    while(window.pollEvent(event)) {
        if(event.type == sf :: Event :: Closed) window.close();
    }
    if(window.getSize() != sf :: Vector2u(width, height)) window.setSize(sf :: Vector2u(width, height));

    deltaTime = clock.restart().asSeconds();
    
    if(scene) {
        scene -> update(deltaTime);
    }
    //std :: cerr << deltaTime << std :: endl;
}
void Game :: render() {
    window.clear();
    renderPool.render(&window);
    window.display();

}
void Game :: run() {
    deltaTime = clock.restart().asSeconds();
    while (window.isOpen()) update(), render();
}
