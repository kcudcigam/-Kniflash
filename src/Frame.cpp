#include "Frame.h"
Frame :: Frame(sf :: Texture* texture, const sf :: IntRect &rect, const sf :: Vector2f &origin) : texture(texture), rect(rect), origin(origin) {

}
Frame :: ~Frame() {

}
void Frame :: load(sf :: Sprite* sprite) const {
    sprite -> setTexture(*texture);
    sprite -> setTextureRect(rect);
    sprite -> setOrigin(origin);
}
std :: vector<Frame> combineFrame(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const sf :: Vector2f &origin) {
    std :: vector<Frame> frameList;
    auto startRect = sf :: IntRect(sf :: Vector2i(start.x * size.x, start.y * size.y), size);
    auto   endRect = sf :: IntRect(sf :: Vector2i(  end.x * size.x,   end.y * size.y), size);
    for(auto current = startRect; current.left <= endRect.left; current.left += size.x)
        frameList.emplace_back(texture, current, origin);
    return frameList;
}

