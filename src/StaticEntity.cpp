#include "StaticEntity.h"
extern RenderPool renderPool;

StaticEntity :: StaticEntity(sf :: Drawable *obj, int layer, int order, const std :: vector<std :: string> &tag)
 : Entity(tag), obj(obj), layer(layer), order(order) {
        
}
StaticEntity :: ~StaticEntity() {
    delete obj;
}
void StaticEntity :: update(const float &deltaTime) {
    if(obj) {
        renderPool.add(obj, getTransform(), layer, order);
    }
    Entity :: update(deltaTime);
}
