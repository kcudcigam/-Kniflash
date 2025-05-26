#include "Rotater.h"
Rotater :: Rotater(const float &velocity, const std :: vector<std :: string> &tag) : Entity(tag), velocity(velocity) {

}
Rotater :: ~Rotater() {

}
void Rotater :: update(const float &deltaTime) {
    Entity :: update(deltaTime);
    if(!super()) return;
    super() -> transform.rotate(velocity * deltaTime);
}
