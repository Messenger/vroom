#ifndef SDL_GAME_H_
#define SDL_GAME_H_

#include <memory>

class World;

class Game
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
public:
    Game();
    ~Game();
    
    bool Running() const;
    void UpdateFrame(World& world);
};

#endif