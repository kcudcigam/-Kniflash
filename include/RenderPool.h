#pragma once
#include "SFML/Graphics.hpp"

class RenderPool {
private:
    std :: vector<std :: pair<std :: pair<int, int>, std :: pair<sf :: Drawable*, sf :: Transform> > > pool;
public:
    void add(sf :: Drawable* obj, sf :: Transform transform = sf :: Transform(), int layer = 0, int order = 0);
    void render(sf :: RenderTarget* target);
};