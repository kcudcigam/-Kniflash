#include "Game.h"
#include <random>
std :: mt19937_64 rnd(std :: chrono :: steady_clock :: now().time_since_epoch().count());
Resource resource;
RenderPool renderPool;
int main() {
    Game game;
    game.run();
    return 0;
}