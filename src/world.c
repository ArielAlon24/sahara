#include <stdio.h>
#include <stdlib.h>

#include "particle.h"
#include "raylib.h"

typedef struct {
    size_t width;
    size_t height;
    size_t particle_size;
    double g_force;
    Particle *particles;
} World;

World *init_world(size_t width, size_t height, size_t particle_size, double g_force) {
    World *w = (World *)malloc(sizeof(World));
    w->width = width;
    w->height = height;
    w->particle_size = particle_size;
    w->g_force = g_force;
    w->particles = malloc(sizeof(Particle) * width * height);
    for (size_t i = 0; i < width * height; i++) {
        w->particles[i] = new_particle(AIR);
    }
    return w;
}

Particle *get_particle(World *world, size_t x, size_t y) {
    Particle *p = world->particles + y * world->width + x;
    return p;
}

void set_particle_type(World *world, size_t x, size_t y, ParticleType type) {
    (world->particles + y * world->width + x)->type = type;
}

void replace_particles(Particle *p0, Particle *p1) {
    ParticleType type = p0->type;
    p0->type = p1->type;
    p1->type = type;

    double velocity = p0->velocity;
    p0->velocity = p1->velocity;
    p1->velocity = velocity;
}

void reset_world(World *world) {
    for (size_t i = 0; i < world->width * world->height; i++) {
        world->particles[i] = new_particle(AIR);
    }
}

void free_world(World *world) {
    free(world->particles);
    free(world);
}

void draw_world(World *world) {
    for (size_t x = 0; x < world->width; x++) {
        for (size_t y = 0; y < world->height; y++) {
            Particle *p = get_particle(world, x, y);
            DrawRectangle(x * world->particle_size, y * world->particle_size, world->particle_size,
                          world->particle_size, particle_type_color(p->type));
        }
    }
}

void update_sand(World *world, size_t x, size_t y, Particle *p0) {
    Particle *p1 = NULL;

    if (y >= world->height - 1) {
        p0->velocity = 1.0;
        return;
    }

    size_t distance = 0;
    size_t max_distance = (size_t)p0->velocity;

    while (distance <= max_distance) {
        if (y + distance + 1 >= world->height) {
            break;
        }

        p1 = get_particle(world, x, y + distance + 1);
        if (p1 == NULL || p1->type == AIR) {
            distance++;
        } else {
            break;
        }
    }

    if (distance > 0) {
        p0->velocity += world->g_force;
        p1 = get_particle(world, x, y + distance);
        p1->is_updated = true;
        replace_particles(p0, p1);
    } else if (rand() % 10 > 8) {
        int dir = (rand() % 2 == 0) ? -1 : 1;
        if (x + dir >= 0 && x + dir < world->width) {
            p1 = get_particle(world, (size_t)x + dir, y + 1);
            if (p1 != NULL && p1->type == AIR) {
                p1->is_updated = true;
                replace_particles(p0, p1);
            }
        }
    }
}

void update(World *world) {
    for (int x = world->width - 1; x >= 0; x--) {
        for (int y = world->height - 1; y >= 0; y--) {
            Particle *p = get_particle(world, x, y);
            if (p) {
                p->is_updated = false;
            }
        }
    }

    for (int x = world->width - 1; x >= 0; x--) {
        for (int y = world->height - 1; y >= 0; y--) {
            Particle *p = get_particle(world, x, y);
            if (p && p->is_updated == false) {
                switch (p->type) {
                case AIR:
                    break;
                case SAND:
                    update_sand(world, x, y, p);
                    break;
                case STONE:
                    break;
                }

                p->is_updated = true;
            }
        }
    }
}
