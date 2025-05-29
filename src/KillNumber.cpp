#include "KillNumber.h"
extern Resource resource;

KillNumber :: KillNumber(int layer, int order, const std :: vector<std :: string> &tag) : Entity(tag), layer(layer), order(order) {
    set(0);
}
KillNumber :: ~KillNumber() {

}
void KillNumber :: set(int number) {
    for(auto child : components) delete child;
    components.clear();
    kill = number;
    const auto img = combineFrame(resource.getImg("props.png"), {0, 42}, {0, 42}, {64, 64}, {0.f, 0.f}).back();
    auto sprite = new sf :: Sprite; img.load(sprite);
    auto icon = new StaticEntity(sprite, layer, order);
    //icon -> transform.scale(1.f, 1.f);
    auto character = new sf :: Text(std :: to_wstring(kill), *resource.getFont("font-title.ttf"), 42);
    character -> setOutlineColor(sf :: Color :: Black);
    character -> setOutlineThickness(4.f);
    character -> setPosition(0.f, 8.f);

    auto text = new StaticEntity(character, layer, order);
    text -> transform.translate(80.f, 0.f);
    addChild(icon), addChild(text);
}