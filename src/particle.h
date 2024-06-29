#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef enum {
    AIR = 0,
    SAND = 1,
    STONE = 2,
} ParticleType;

Color particle_type_color(ParticleType type);

typedef struct {
    ParticleType type;
    float velocity;
    bool is_updated;
} Particle;

Particle new_particle(ParticleType type);

#endif
