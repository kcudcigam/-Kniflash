#include "StaticEntity.h"
extern RenderPool renderPool;

StaticEntity :: StaticEntity(sf :: Drawable *obj, int layer, int order, const std :: vector<std :: string> &tag, bool combineTransform)
 : Entity(tag), obj(obj), layer(layer), order(order), combineTransform(combineTransform) {
        
}
StaticEntity :: ~StaticEntity() {
    delete obj;
}
void StaticEntity :: set(sf :: Drawable *obj) {
    if(this -> obj) {
        delete this -> obj;
    }
    this -> obj = obj;
}
void StaticEntity :: setStatus(bool status) {
    active = status;
}
sf :: Drawable* StaticEntity :: get() {
    return obj;
}
void StaticEntity :: update(const float &deltaTime) {
    if(!active) return;
    Entity :: update(deltaTime);
    
    if(obj) {
        if(combineTransform) renderPool.add(obj, getTransform(), layer, order);
        else renderPool.add(obj, transform, layer, order);
    }
}
