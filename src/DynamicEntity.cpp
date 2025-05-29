#include "DynamicEntity.h"
extern RenderPool renderPool;

DynamicEntity :: DynamicEntity(int layer, int order, const std :: vector<std :: string> &tag)
 : Entity(tag), layer(layer), order(order) {
        
}
DynamicEntity :: ~DynamicEntity() {
    
}
void DynamicEntity :: add(const std :: string &key, const Animation &value) {
    animations.emplace(key, value);
    animations.at(key).reset();
}
void DynamicEntity :: reset() {
    if(currentAnimation != "") animations.at(currentAnimation).reset();
}
void DynamicEntity :: play(std :: string key, bool priority) {
    if(key == currentAnimation) {
        return;
    }
    if(currentAnimation != "") {
        if(!priority && fixed && !animations.at(currentAnimation).end()) {
            return;
        }
        animations.at(currentAnimation).reset();
    }
    fixed = priority;
    currentAnimation = key;
}
sf :: Sprite* DynamicEntity :: get() {
    return &sprite;
}
const Animation* DynamicEntity :: getAnimation(const std :: string &animation) const {
    if(!animations.contains(animation)) return nullptr;
    return &animations.at(currentAnimation);
}
void DynamicEntity :: update(const float& deltaTime) {
    Entity :: update(deltaTime);
    if(animations.contains(currentAnimation) && !animations.at(currentAnimation).end()) {
        animations.at(currentAnimation).play(&sprite, deltaTime);
        renderPool.add(&sprite, getTransform(), layer, order);
    }
}
