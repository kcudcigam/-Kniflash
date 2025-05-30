#pragma once
#include "StaticEntity.h"
#include "SignalPool.h"
#include "Resource.h"

class Button : public Entity {
private:
    uint64_t receiver;
    std :: string signal;
    bool pressed = false, activated = false;
    sf :: Text* character = nullptr;
public:
    Button(uint64_t receiver, const std :: string &signal, const std :: wstring & text, sf :: Font* font, int size, const sf :: Vector2f &position, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
    virtual ~Button();
    sf :: Text* get();
    virtual void update(const float &deltaTime);
};
