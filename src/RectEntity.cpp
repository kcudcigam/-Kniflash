#include "RectEntity.h"
extern RenderPool renderPool;
RectEntity :: RectEntity(sf :: FloatRect rect, const std :: vector<std :: string> &tag) : Entity(tag), rect(rect) {

}
RectEntity :: ~RectEntity() {

}
sf :: FloatRect RectEntity :: getLocalRect() const {
    return rect;
}
sf :: FloatRect RectEntity :: getGlobalRect() const {
    return getTransform().transformRect(rect);
}
void RectEntity :: setRect(sf :: FloatRect rect) {
    this -> rect = rect;
}
void RectEntity :: render(){
    outline.setPosition({rect.left, rect.top});
    outline.setSize({rect.width, rect.height});
    outline.setFillColor(sf :: Color :: Transparent);
    outline.setOutlineThickness(-10.f);
    outline.setOutlineColor(sf :: Color :: Green);
    renderPool.add(&outline, getTransform(), 999);
}
void RectEntity :: update(const float &deltaTime) {
    render();
    Entity :: update(deltaTime);
}
