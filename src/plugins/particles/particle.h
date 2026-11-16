#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../code/Enemies/Fishoder/fishoder.h"
#include "../../code/Enemies/Shadowner/shadowner.h"
#include "../../code/Enemies/Spikader/spikader.h"
#include "../../code/Platform/platform.h"
#include "../../assets/download/assets.h"

#include <vector>

struct Particle {
    float x, y;
    float vx, vy;
    int lifetime;
    int maxLifetime;
    bool active;
    bool fire;
    SDL_Texture* sprite;
    float angle;
    SDL_Color color;
    SDL_FRect collide;
};

class ParticleSys {
private:
    std::vector<Particle> pool;
    int maxParticles;

public:
    ParticleSys(int count);
    ~ParticleSys();

    void emit(float x, float y, float vx, float vy, int lifetime, float angle, SDL_Texture* sprite, bool fire, SDL_Color color);
    void damage(std::vector<Fishoder> &fish, std::vector<Shadowner> &shad, std::vector<Spikader> &spik, std::vector<Platform> &plat);
    void update();
    void render(SDL_Renderer* renderer, SDL_FPoint campos);
};

#endif
