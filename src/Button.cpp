#include "Button.h"
extern SignalPool signalPool;
extern Resource resource;

Button :: Button(uint64_t receiver, const std :: string &signal, const std :: wstring &text, sf :: Font* font, int size, const sf :: Vector2f &position, int layer, int order, const std :: vector<std :: string> & tag)
 : receiver(receiver), signal(signal), Entity(tag) {
    character = new sf :: Text(text, *font, size);
    const sf :: FloatRect &textRect = character -> getLocalBounds();
    character -> setOrigin(textRect.left + textRect.width / 2.f, textRect.top  + textRect.height / 2.f);
    character -> setPosition(position);
    addChild(new StaticEntity(character, layer, order));
}
Button :: ~Button() {

}
sf :: Text* Button :: get() {
    return character;
}
void Button :: update(const float &deltaTime) {
    sf :: Vector2f position = {
        static_cast<float>(sf :: Mouse :: getPosition(*(root() -> getWindow())).x),
        static_cast<float>(sf :: Mouse :: getPosition(*(root() -> getWindow())).y)};
    sf :: Vector2f size = {
        static_cast<float>(root() -> getWindow() -> getSize().x),
        static_cast<float>(root() -> getWindow() -> getSize().y)};
    auto bounds = character -> getGlobalBounds();
    position += (root() -> getWindow() -> getView()).getCenter() - size / 2.f;
    if(sf :: FloatRect(bounds.getPosition() + getTransform().transformPoint(0.f, 0.f), bounds.getSize()).contains(position.x, position.y)) {
        character -> setFillColor(sf :: Color :: White);
        if(sf :: Mouse :: isButtonPressed(sf :: Mouse :: Button :: Left)) {
            pressed = true;
        }
        if(pressed && !sf :: Mouse :: isButtonPressed(sf :: Mouse :: Button :: Left)) {
            activated = true;
            signalPool.add(receiver, signal);
            resource.getSound("click.wav") -> play();
        }
    }
    else {
        character -> setFillColor(sf :: Color(180, 180, 180));
    }
    Entity :: update(deltaTime);
}