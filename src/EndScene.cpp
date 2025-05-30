#include "EndScene.h"
extern Resource resource;
extern SignalPool signalPool;


EndScene :: EndScene(sf :: RenderWindow* window, int skin, float clock, std :: pair<int, int> rank, int kills) : Entity() {
    resource.getSound("game.ogg") -> stop();

    auto shade = new sf :: RectangleShape();
    shade -> setSize(sf :: Vector2f (static_cast<float>(window -> getSize().x) + 2.f, static_cast<float>(window -> getSize().y) + 2.f));
    shade -> setOrigin(shade -> getSize() / 2.f);
    shade -> setFillColor(sf :: Color :: Black);
    addChild(new StaticEntity(shade, 20, 0, {"endShade"}));

    auto text = new sf :: Text(rank.first == 1 ? L"You Win" : L"Game Over", *resource.getFont("font-title.ttf"), 180);
    const sf::FloatRect &textRect = text -> getLocalBounds();
    text -> setOrigin(textRect.left + textRect.width / 2.f, textRect.top  + textRect.height / 2.f);
    auto title = new StaticEntity(text, 500, 0, {"title"});
    title -> transform.translate(0.f, -450.f);
    addChild(title);

    auto clockText = new StaticEntity(new sf :: Text(L"存活时间: " + std :: to_wstring(int(clock + 0.5)) + L" 秒", *resource.getFont("font-button.ttf"), 64), 500, 0, {"clock"});
    clockText -> transform.translate(100.f, -110.f);
    auto rankText = new StaticEntity(new sf :: Text(L"排名: " + std :: to_wstring(rank.first) + L" / " + std :: to_wstring(rank.second), *resource.getFont("font-button.ttf"), 64), 500, 0, {"rank"});
    rankText -> transform.translate(100.f, 40.f);
    auto killText = new StaticEntity(new sf :: Text(L"击杀数目: " + std :: to_wstring(kills), *resource.getFont("font-button.ttf"), 64), 500, 0, {"kill"});
    killText -> transform.translate(100.f, 190.f);
    addChild(clockText);
    addChild(rankText);
    addChild(killText);


    auto character = new DynamicEntity(500, 0, {"character"});
    character -> transform.translate(-300.f, 0.f);
    character -> transform.scale(18.f, 18.f);
    const std :: string &img = "Character " + std :: to_string(skin) + ".png";
    character -> add("idle", Animation(combineFrame(resource.getImg(img), {0, 0}, {3, 0}, {64, 64}, {32.f, 32.f}), 0.15f));
    character -> play("idle");
    addChild(character);


    addChild(new Button(0, "start", L"返回", resource.getFont("font-button.ttf"), 64, sf :: Vector2f(0.f, 450.f), 500, 0, {"exitButton"}));

    addChild(new Transparency(uuid(), "shadeTransparency", 0.f, 225.f, 0.5));
    addChild(new Transparency(uuid(), "titleTransparency", 0.f, 255.f, 0.8));
    addChild(new Transparency(uuid(), "characterTransparency", 0.f, 255.f, 0.5, 0.8));
    addChild(new Transparency(uuid(), "clockTransparency", 0.f, 255.f, 0.5, 1.2));
    addChild(new Transparency(uuid(), "rankTransparency", 0.f, 255.f, 0.5, 1.4));
    addChild(new Transparency(uuid(), "killTransparency", 0.f, 255.f, 0.5, 1.6));
    addChild(new Transparency(uuid(), "exitTransparency", 0.f, 255.f, 0.5, 2.2));

    if(rank.first == 1) resource.getSound("win.ogg") -> play();
    else resource.getSound("over.ogg") -> play();

    //std :: cerr << skin << ' ' << clock << ' ' << rank.first << '/' << rank.second << ' ' << kills << std :: endl;
}
EndScene :: ~EndScene() {
    resource.getSound("win.ogg") -> stop();
    resource.getSound("over.ogg") -> stop();
}
void EndScene :: update(const float& deltaTime) {
    Entity :: update(deltaTime);

    auto shade = static_cast<sf :: RectangleShape*>(static_cast<StaticEntity*>(find("endShade").back()) -> get());
    shade -> setFillColor(sf :: Color(shade -> getFillColor().r, shade -> getFillColor().g, shade -> getFillColor().b, signalPool.query(uuid(), "shadeTransparency")));
    auto title = static_cast<sf :: Text*>(static_cast<StaticEntity*>(find("title").back()) -> get());
    title -> setFillColor(sf :: Color(title -> getFillColor().r, title -> getFillColor().g, title -> getFillColor().b, signalPool.query(uuid(), "titleTransparency")));

    auto character = static_cast<DynamicEntity*>(find("character").back()) -> get();
    character -> setColor(sf :: Color(character -> getColor().r, character -> getColor().g, character -> getColor().b, signalPool.query(uuid(), "characterTransparency")));

    auto clock = static_cast<sf :: Text*>(static_cast<StaticEntity*>(find("clock").back()) -> get());
    clock -> setFillColor(sf :: Color(clock -> getFillColor().r, clock -> getFillColor().g, clock -> getFillColor().b, signalPool.query(uuid(), "clockTransparency")));
    auto rank = static_cast<sf :: Text*>(static_cast<StaticEntity*>(find("rank").back()) -> get());
    rank -> setFillColor(sf :: Color(rank -> getFillColor().r, rank -> getFillColor().g, rank -> getFillColor().b, signalPool.query(uuid(), "rankTransparency")));
    auto kill = static_cast<sf :: Text*>(static_cast<StaticEntity*>(find("kill").back()) -> get());
    kill -> setFillColor(sf :: Color(kill -> getFillColor().r, kill -> getFillColor().g, kill -> getFillColor().b, signalPool.query(uuid(), "killTransparency")));

    auto exit = static_cast<Button*>(find("exitButton").back()) -> get();
    exit -> setFillColor(sf :: Color(exit -> getFillColor().r, exit -> getFillColor().g, exit -> getFillColor().b, signalPool.query(uuid(), "exitTransparency")));
}