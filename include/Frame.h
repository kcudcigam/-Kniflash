#pragma once
#include "SFML/Graphics.hpp"

struct Frame {
    sf :: Texture* texture;
    sf :: IntRect rect;
    sf :: Vector2f origin;
    Frame(sf :: Texture* texture = nullptr, const sf :: IntRect &rect = sf :: IntRect(), const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));
};
std :: vector<Frame> combineFrame(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));
