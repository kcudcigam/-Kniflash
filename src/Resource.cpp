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
    loadSound(directory / "sound");
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
        //std :: cerr << file.path().filename().string() << std :: endl;
    }
}
void Resource :: loadSound(const std :: filesystem ::path &directory) {
    using json = nlohmann :: json;
    const json config(json :: parse(std :: ifstream(directory / "config.json")));
    
    for (const auto &file : std :: filesystem :: directory_iterator(directory)) {
        if(!config.contains(file.path().filename().string())) continue;
        auto soundBuffer = new sf :: SoundBuffer(); soundBuffer -> loadFromFile(file.path().string());
        this -> soundBuffer.emplace(file.path().filename().string(), soundBuffer);
        auto music = new sf :: Sound(*soundBuffer);
        music -> setVolume(config[file.path().filename().string()]["volume"].get<float>());
        music -> setLoop(config[file.path().filename().string()]["loop"].get<bool>());
        if(config[file.path().filename().string()].contains("pitch")) {
            music -> setPitch(config[file.path().filename().string()]["pitch"].get<float>());
        }
        this -> sound.emplace(file.path().filename().string(), music);
        //std :: cerr << file.path().filename().string() << std :: endl;
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