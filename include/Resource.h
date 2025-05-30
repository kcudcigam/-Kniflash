#pragma once
#include <fstream>
#include <filesystem>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "Json.hpp"
#include "Animation.h"

class Resource {
private:
    std :: map <std :: string, sf :: Texture*> img;
    std :: map <std :: string, sf :: Font*> font;
    std :: map <std :: string, sf :: SoundBuffer*> soundBuffer;
    std :: map <std :: string, sf :: Sound*> sound;
    
    void loadImg(const std :: filesystem :: path &directory);
    void loadMap(const std :: filesystem :: path &directory);
    void loadFont(const std :: filesystem :: path &directory);
    void loadSound(const std :: filesystem :: path &directory);
public:
    Resource();
    virtual ~Resource();
    void loadFrom(const std :: filesystem :: path &directory);
    sf :: Texture* getImg(const std :: string &file) const;
    sf :: Font* getFont(const std :: string &file) const;
    sf :: Sound* getSound(const std :: string &file) const;
};