#include "Entity.h"
extern std :: mt19937_64 rnd;

Entity :: Entity(const std :: vector<std :: string> &tag) : ancestor(nullptr), id(rnd()) {
    for(const auto &i : tag) tags[i] = true;
}
Entity :: ~Entity() {
    for(auto child : components) {
        delete child;
    }
}
const Entity* Entity :: super() const {
    return ancestor;
}
const Entity* Entity :: root() const {
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
}
std :: vector<Entity*> Entity :: find(const std :: string &tag) {
    std :: vector<Entity*> res;
    if(contains(tag)) res.emplace_back(this);
    for(const auto child : components) {
        auto tmp = child -> find(tag);
        res.insert(res.end(), tmp.begin(), tmp.end());
    }
    return res;
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
