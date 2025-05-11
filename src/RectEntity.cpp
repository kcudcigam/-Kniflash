#include "RectEntity.h"
extern RenderPool renderPool;
RectEntity :: RectEntity(sf :: FloatRect rect) : rect(rect) {

}
RectEntity :: ~RectEntity() {
    for(auto outline : outlines) delete outline;
}
sf :: FloatRect RectEntity :: getRect() const {
    return rect;
}
void RectEntity :: setRect(sf :: FloatRect rect) {
    this -> rect = rect;
}
void RectEntity :: render(){
    auto outline = new sf :: RectangleShape;
    outline -> setPosition({rect.left, rect.top});
    outline -> setSize({rect.width, rect.height});
    outline -> setFillColor(sf :: Color :: Transparent);
    outline -> setOutlineThickness(-10.f);
    outline -> setOutlineColor(sf :: Color :: Green);
    renderPool.add(outline, getTransform(), 999);
    outlines.emplace_back(outline);
}
void RectEntity :: update(const float &deltaTime) {
    render();
    for(auto child : components) {
        child -> update(deltaTime);
    }
}
