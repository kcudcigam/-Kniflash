#include "Animation.h"

Animation :: Animation(const std :: vector<Frame> &list, const float &duration, bool loop)
: list(list), duration(duration), loop(loop), paused(false) {
    reset();
}
Animation :: ~Animation() {

}
void Animation :: setLoop(bool loop) {
    this -> loop = loop;
}
void Animation :: pause() {
    paused = true;
}
void Animation :: run() {
    paused = false;
}
bool Animation :: end() const {
    return it == list.size();
}
void Animation :: play(sf :: Sprite *sprite, const float &deltaTime) {
    if(end()) return;
    if(!paused) currentTime += deltaTime;
    if(currentTime > duration) {
        currentTime = 0.f, it++;
    }
    if(end()) {
        if(loop) it = 0;
        else return;
    }
    sprite -> setTexture(*list[it].texture);
    sprite -> setTextureRect(list[it].rect);
    sprite -> setOrigin(list[it].origin);
}
void Animation :: reset() {
    currentTime = 0.f; it = 0;
}

