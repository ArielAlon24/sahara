#include <stdlib.h>

#include "raylib.h"
#include <stdbool.h>

typedef enum {
    AIR = 0,
    SAND = 1,
    STONE = 2,
} ParticleType;

Color particle_type_color(ParticleType type) {
    switch (type) {
    case AIR:
        return BLACK;
    case SAND: {
        Color c = {213, 152, 92, 255};
        return c;
    }
    case STONE: {
        Color c = {38, 36, 30, 255};
        return c;
    }
    default:
        return BLACK;
    }
}

typedef struct {
    ParticleType type;
    double velocity;
    bool is_updated;
} Particle;

Particle new_particle(ParticleType type) {
    Particle p = {type, 1.0, true};
    return p;
}
