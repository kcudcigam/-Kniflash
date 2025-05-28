#include "Button.h"
#include <iostream>
extern SignalPool signalPool;

Button :: Button(uint64_t receiver, const std :: string &signal, const std :: wstring &text, sf :: Font* font, int size, const sf :: Vector2f &position, int layer, int order, const std :: vector<std :: string> & tag)
 : receiver(receiver), signal(signal), Entity(tag) {
    character = new sf :: Text(text, *font, size);
    const sf::FloatRect &textRect = character -> getLocalBounds();
    character -> setOrigin(textRect.left + textRect.width / 2.f, textRect.top  + textRect.height / 2.f);
    character -> setPosition(position);
    bounds = character -> getGlobalBounds();
    addChild(new StaticEntity(character, layer, order));
}
Button :: ~Button() {

}
void Button :: update(const float &deltaTime) {
    sf::Vector2f position = {sf :: Mouse :: getPosition(*(root() -> getWindow())).x, sf :: Mouse :: getPosition(*(root() -> getWindow())).y};
    position += (root() -> getWindow() -> getView()).getViewport().getPosition();
    std :: cerr << bounds.left << ' ' << bounds.top << ' ' << bounds.width << ' ' << bounds.height << std :: endl;
    std :: cerr << position.x << ' ' << position.y << std :: endl;
    if(bounds.contains(position.x, position.y)) {
        character -> setFillColor(sf :: Color :: White);
        if(sf :: Mouse :: isButtonPressed(sf :: Mouse :: Button :: Left)) {
            pressed = true;
        }
        if(pressed && !sf :: Mouse :: isButtonPressed(sf :: Mouse :: Button :: Left)) {
            activated = true;
            signalPool.add(receiver, signal);           
        }
    }
    else {
        character -> setFillColor(sf :: Color :: Black);
    }
    Entity :: update(deltaTime);
}