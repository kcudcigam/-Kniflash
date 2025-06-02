#include "Entity.h"
extern std :: mt19937_64 rnd;

Entity :: Entity(const std :: vector<std :: string> &tag, sf :: RenderWindow* window) : ancestor(nullptr), id(rnd()), window(window) {
    for(const auto &i : tag) {
        tags[i] = true;
        sub[i].emplace_back(this);
    }
    ids[uuid()] = this;
}
Entity :: ~Entity() {
    for(auto child : components) {
        delete child;
    }
    auto p = super();
    while(p) p -> ids.erase(uuid()), p = p -> super();
}
Entity* Entity :: super() {
    return ancestor;
}
Entity* Entity :: root() {
    return super() == nullptr ? this : super() -> root();
}
bool Entity :: contains(const std :: string &tag) const {
    return tags.contains(tag);
}
uint64_t Entity :: uuid() const {
    return id;
}
void Entity :: addChild(Entity* child) {
    components.emplace_back(child);
    child -> ancestor = this;
    for(const auto &[tag, its] : child -> sub) {
        auto p = this;
        while(p) {
            auto &s = p -> sub[tag];
            for(auto it : its) s.emplace_back(it);
            p = p -> super();
        }
    }
    for(const auto &[i, it] : child -> ids) {
        auto p = this;
        while(p) {
            p -> ids[i] = it;
            p = p -> super();
        }
    }
}
std :: vector<Entity*> Entity :: find(const std :: string &tag) {
    if(!sub.contains(tag)) return {};
    return sub.at(tag);
}
Entity* Entity :: find(uint64_t uuid) {
    if(!ids.contains(uuid)) return nullptr;
    return ids.at(uuid);
}
sf :: RenderWindow* Entity :: getWindow() const {
    return window;
} 
sf :: Transform Entity :: getTransform() const {
    if(ancestor == nullptr) return transform;
    return ancestor -> getTransform() * transform;
}
void Entity :: update(const float &deltaTime) {
    for(auto child : components) {
        child -> update(deltaTime);
    }
}
