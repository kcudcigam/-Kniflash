#include "SoundPlayer.h"
extern Resource resource;

SoundPlayer :: SoundPlayer(const std :: string &listener, const std :: vector<std :: string> &tag) : listener(listener), Entity(tag) {

}
SoundPlayer :: ~SoundPlayer() {
    for(auto it : sounds) {
        it -> stop();
        delete it;
    }
}
#include <iostream>
void SoundPlayer :: play(const std :: string &name) {
    if(root() -> find(listener).empty()) return;
    auto d = (root() -> find(listener).back()) -> getTransform().transformPoint(0.f, 0.f) - getTransform().transformPoint(0.f, 0.f);
    const float r = k * sqrt(d.x * d.x + d.y * d.y);
    if(r > 0.2) return;
    auto it = new sf :: Sound(*resource.getSound(name));
    const float v = 1.f / sqrt(it -> getVolume());
    const float s = (r + v) * (r + v);
    it -> setVolume(1.f / s);
    sounds.emplace_back(it);
    it -> play();
}
void SoundPlayer :: update(const float &deltaTime) {
    std :: vector<sf :: Sound*> tmp;
    for(auto it : sounds) {
        if(it -> getStatus() == sf :: SoundSource :: Status :: Stopped) delete it;
        else tmp.emplace_back(it);
    }
    swap(tmp, sounds);
    Entity :: update(deltaTime);
}