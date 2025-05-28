#include "Resource.h"

//Resource
Resource :: Resource() {

}
Resource :: ~Resource() {
    for(auto it : sound) {
        it.second -> stop(); delete it.second;
    }
    for(auto it : img) delete it.second;
    for(auto it : font) delete it.second;
    for(auto it : soundBuffer) delete it.second;
}
void Resource :: loadFrom(const std :: filesystem :: path &directory) {
    loadImg(directory / "image");
    loadFont(directory / "font");
    //loadSound(directory / "sound");
    // for(const std :: string &music : {"menu", "game", "win", "dead"})
    //     getSound(music + ".wav") -> setLoop(true), getSound(music + ".wav") -> setVolume(5.f);
    // getSound("footstep.wav") -> setPitch(1.4f);
    // getSound("footstep.wav") -> setVolume(2.f);
    // getSound("attack.wav") -> setVolume(40.f);
    // getSound("metal-small.wav") -> setVolume(20.f);
    // getSound("metal-ringing.wav") -> setVolume(5.f);
    // getSound("hit.wav") -> setVolume(10.f);
    // getSound("door.wav") -> setVolume(4.f);
    // getSound("pass.wav") -> setVolume(10.f);
    // getSound("click.wav") -> setVolume(10.f);
}
void Resource :: loadImg(const std :: filesystem :: path &directory) {
    for (const auto &img : std :: filesystem :: directory_iterator(directory)) {
        if(std :: filesystem :: is_directory(img)) loadImg(img.path());
        else {
            auto texture = new sf :: Texture(); texture -> loadFromFile(img.path().string());
            this -> img.emplace(img.path().filename().string(), texture);
            //std :: cerr << img.path().filename().string() << std :: endl;
        }
    }
}
void Resource :: loadFont(const std :: filesystem ::path &directory) {
    for (const auto &file : std :: filesystem :: directory_iterator(directory)) {
        auto font = new sf :: Font(); font -> loadFromFile(file.path().string());
        this -> font.emplace(file.path().filename().string(), font);
    }
}
void Resource :: loadSound(const std :: filesystem ::path &directory) {
    for (const auto &file : std :: filesystem :: directory_iterator(directory)) {
        auto soundBuffer = new sf :: SoundBuffer(); soundBuffer -> loadFromFile(file.path().string());
        this -> soundBuffer.emplace(file.path().filename().string(), soundBuffer);
        this -> sound.emplace(file.path().filename().string(), new sf :: Sound(*soundBuffer));
    }
}
sf :: Texture* Resource :: getImg(const std :: string &file) const {
    return img.at(file);
}
sf :: Font* Resource :: getFont(const std :: string &file) const {
    return font.at(file);
}
sf :: Sound* Resource :: getSound(const std :: string &file) const {
    return sound.at(file);
}