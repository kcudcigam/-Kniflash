#include "KnifeManager.h"

KnifeManager :: KnifeManager(const std :: vector<std :: string> &tag) : Entity(tag) {
    
}
KnifeManager :: ~KnifeManager() {

}
void KnifeManager :: update(const float& deltaTime) {
    std :: vector<Entity*> knives;
    for(auto knife : components) {
        if(static_cast<FlyKnife*>(knife) -> isActive())
            knives.emplace_back(knife);
        else {
            delete knife;
        }
    }
    swap(components, knives);
    Entity :: update(deltaTime);
}
