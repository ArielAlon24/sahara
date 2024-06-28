#ifndef WORLD_H
#define WORLD_H

#include "particle.h"
#include "raylib.h"

typedef struct {
    size_t width;
    size_t height;
    size_t particle_size;
    double g_force;
    Particle *particles;
} World;

World *init_world(size_t width, size_t height, size_t particle_size, double g_force);
Particle *get_particle(World *world, size_t x, size_t y);
void set_particle_type(World *world, size_t x, size_t y, ParticleType type);
void reset_world(World *world);
void free_world(World *world);
void draw_world(World *world);
void update(World *world);

#endif
