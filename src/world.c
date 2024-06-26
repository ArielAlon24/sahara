#include <stdio.h>
#include <stdlib.h>

#include "particle.h"
#include "raylib.h"

#define PARTICLE_SIZE 10

typedef struct {
  int width;
  int height;
  int particleSize;
  Particle *particles;
} World;

World *initWorld(int width, int height, int particleSize) {
  World *w = (World *)malloc(sizeof(World));
  w->width = width;
  w->height = height;
  w->particleSize = particleSize;
  w->particles = malloc(sizeof(Particle) * width * height);
  for (int i = 0; i < width * height; i++) {
    w->particles[i] = PARTICLE_AIR;
  }
  return w;
}

Particle *getParticle(World *world, int x, int y) {
  Particle *p = world->particles + y * world->width + x;
  return p;
}

void setParticle(World *world, int x, int y, Particle p) {
  *(world->particles + y * world->width + x) = p;
}

void freeWorld(World *world) {
  free(world->particles);
  free(world);
}

void DrawWorld(World *world) {
  for (int x = 0; x < world->width; x++) {
    for (int y = 0; y < world->height; y++) {
      Particle *p = getParticle(world, x, y);
      DrawRectangle(x * world->particleSize, y * world->particleSize,
                    world->particleSize, world->particleSize, getColor(*p));
    }
  }
}

void update(World *world) {
  for (int y = world->height - 1; y >= 0; y--) {
    for (int x = world->width - 1; x >= 0; x--) {
      Particle *p = world->particles + y * world->width + x;
      if (*p == PARTICLE_AIR) {
        continue;
      }

      if (y < world->height - 1) {
        if (*getParticle(world, x, y + 1) == PARTICLE_AIR) {
          setParticle(world, x, y + 1, PARTICLE_SAND);
          setParticle(world, x, y, PARTICLE_AIR);
        } else if (x > 0 && *getParticle(world, x - 1, y + 1) == PARTICLE_AIR) {
          setParticle(world, x - 1, y + 1, PARTICLE_SAND);
          setParticle(world, x, y, PARTICLE_AIR);
        } else if (x < world->width - 1 &&
                   *getParticle(world, x + 1, y + 1) == PARTICLE_AIR) {
          setParticle(world, x + 1, y + 1, PARTICLE_SAND);
          setParticle(world, x, y, PARTICLE_AIR);
        }
      }
    }
  }
}
