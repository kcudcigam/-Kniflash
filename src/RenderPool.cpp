#include "RenderPool.h"

void RenderPool :: add(sf :: Drawable* obj, sf :: Transform transform, int layer, int order) {
    pool.emplace_back(std :: make_pair(layer, order), std :: make_pair(obj, transform));
}
void RenderPool :: render(sf :: RenderTarget* target) {
    sort(pool.begin(), pool.end(), [](const auto &x, const auto &y) {return x.first < y.first;});
    for(const auto &obj : pool) {
        target -> draw(*obj.second.first, obj.second.second);
    }
    pool.clear();
}