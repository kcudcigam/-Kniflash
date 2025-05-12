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
void DynamicEntity :: play(std :: string key, bool priority) {
    if(key == currentAnimation && !animations.at(currentAnimation).end()) {
        return;
    }
    if(!priority && fixed && !animations.at(currentAnimation).end()) {
        return;
    }
    fixed = priority;
    if(currentAnimation != "") {
        animations.at(currentAnimation).reset();
    }
    currentAnimation = key;
}
void DynamicEntity :: update(const float& deltaTime)  {
    if(animations.contains(currentAnimation)) {
        animations.at(currentAnimation).play(&sprite, deltaTime);
        renderPool.add(&sprite, getTransform(), layer, order);
    }
    Entity :: update(deltaTime);
}
