#pragma once
#include "SFML/Graphics.hpp"

class Frame {
private:
    sf :: Texture* texture;
    sf :: IntRect rect;
    sf :: Vector2f origin;
public:
    Frame(sf :: Texture* texture = nullptr, const sf :: IntRect &rect = sf :: IntRect(), const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));
    ~Frame();
    void load(sf :: Sprite* sprite) const;
};
std :: vector<Frame> combineFrame(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));
