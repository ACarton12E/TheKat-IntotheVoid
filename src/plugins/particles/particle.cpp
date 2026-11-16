#include "particle.h"


ParticleSys::ParticleSys(int count) : maxParticles(count) {
    pool.resize(maxParticles);
    for (int i = 0; i < maxParticles; i++) {
        pool[i].active = false;
    }
}


ParticleSys::~ParticleSys() {};

void ParticleSys::emit(float x, float y, float vx, float vy, int lifetime, float angle, SDL_Texture* sprite, bool fire, SDL_Color color) {
    for (int i = 0; i < maxParticles; i++) {
        if (!pool[i].active) {
            pool[i].x = x;
            pool[i].y = y;
            pool[i].collide.x = x;
            pool[i].collide.y = y;
            pool[i].lifetime = lifetime;
            pool[i].maxLifetime = lifetime;
            pool[i].sprite = sprite;
            pool[i].active = true;
            pool[i].vx = vx;
            pool[i].vy = vy;
            pool[i].fire = fire;
            pool[i].color = color;
            pool[i].angle = angle;
            break;
        }
    }
}

void ParticleSys::update() {
    for (int i = 0; i < maxParticles; i++) {
        if (pool[i].active) {
            pool[i].x += pool[i].vx;
            pool[i].y += pool[i].vy;

            pool[i].lifetime--;

            float t = 1.0f - (static_cast<float>(pool[i].lifetime) / static_cast<float>(pool[i].maxLifetime));
            float size = 25.0f * t;

            pool[i].collide.x = pool[i].x;
            pool[i].collide.y = pool[i].y;
            pool[i].collide.w = size;
            pool[i].collide.h = size;

            if (pool[i].fire) {


                pool[i].angle += 0.05f;

                float t = 1.0f - (static_cast<float>(pool[i].lifetime) / static_cast<float>(pool[i].maxLifetime));

                if (t < 0.1f) {

                    float tstat = t / 0.1f;
                    pool[i].color.r = 255;
                    pool[i].color.g = 255;
                    pool[i].color.b = static_cast<Uint8>(255 * (1.0f - tstat));
                    pool[i].color.a = static_cast<Uint8>(255 * tstat);

                } else if (t < 0.4) {
                    float tstat = (t - 0.1f) / 0.3f;
                    pool[i].color.r = 255;
                    pool[i].color.g = static_cast<Uint8>(255 - (115 * tstat));
                    pool[i].color.b = 0;
                    pool[i].color.a = 255;
                } else if (t < 0.7) {

                    float tstat = (t - 0.4f) / 0.3f;
                    pool[i].color.r = 255;
                    pool[i].color.g = static_cast<Uint8>(140 - (140 * tstat));
                    pool[i].color.b = 0;
                    pool[i].color.a = static_cast<Uint8>(255 - (75 * tstat));

                } else {
                    float tstat = (t - 0.7f) / 0.3f;
                    if (tstat > 1.0f) tstat = 1.0f;

                    pool[i].color.r = static_cast<Uint8>(255 - (175 * tstat));
                    pool[i].color.g = static_cast<Uint8>(80 * tstat);
                    pool[i].color.b = static_cast<Uint8>(80 * tstat);

                    pool[i].color.a = static_cast<Uint8>(180 * (1.0f - tstat));
                }
            }

            if (pool[i].lifetime <= 0) {
                pool[i].active = false;
            }
        }
    }
}

void ParticleSys::damage(
    std::vector<Fishoder> &fish,
    std::vector<Shadowner> &shad,
    std::vector<Spikader> &spik,
    std::vector<Platform> &plat
) {
    for (int i = 0; i < maxParticles; i++) {
        if (pool[i].active) {
            for ( Fishoder &fishoder : fish ) {
                if (SDL_HasIntersectionF(&pool[i].collide, &fishoder.collide) && (!fishoder.dead && fishoder.active)) {
                    Mix_PlayChannel(-1, Assets::Sounds::DamageEnemie, 0);
                    fishoder.dead = true;
                }
            }
            for ( Shadowner &shadowner : shad ) {
                if (SDL_HasIntersectionF(&pool[i].collide, &shadowner.collide) && (!shadowner.dead && shadowner.active)) {
                    Mix_PlayChannel(-1, Assets::Sounds::DamageEnemie, 0);
                    shadowner.dead = true;
                }
            }
            for ( Platform &platform : plat ) {
                if ((SDL_HasIntersectionF(&pool[i].collide, &platform.collide) && platform.sprite == Assets::Platforms[1]) && !platform.explote) {
                    Mix_VolumeChunk(Assets::Sounds::Explotion, 25);
                    Mix_PlayChannel(-1, Assets::Sounds::Explotion, 0);
                    platform.Explote(fish, shad, spik, plat);
                    platform.explote = true;
                }
            }
        }
    }
}

void ParticleSys::render(SDL_Renderer* renderer, SDL_FPoint campos) {
    for (int i = 0; i < maxParticles ; i++) {
        if (pool[i].active) {
            SDL_SetRenderDrawColor(renderer, pool[i].color.r, pool[i].color.g, pool[i].color.b, pool[i].color.a);

            float t = 3.0f - (static_cast<float>(pool[i].lifetime) / static_cast<float>(pool[i].maxLifetime));

            SDL_FRect rect = {
                static_cast<float>(pool[i].x - campos.x),
                static_cast<float>(pool[i].y - campos.y),
                8.5f * (3.0f + t),
                8.5f * (3.0f + t)
            };

            SDL_SetTextureColorMod(pool[i].sprite, pool[i].color.r, pool[i].color.g, pool[i].color.b);
            SDL_SetTextureAlphaMod(pool[i].sprite, pool[i].color.a);
            SDL_RenderCopyExF(renderer, pool[i].sprite, NULL, &rect, pool[i].angle, NULL, SDL_FLIP_NONE);
        }
    }
}