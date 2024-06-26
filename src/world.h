#include "particle.h"
#include "raylib.h"

typedef struct {
  int width;
  int height;
  Particle *particles;
} World;

World *initWorld(int width, int height, int particleSize);

Particle *getParticle(World *world, int x, int y);

void setParticle(World *world, int x, int y, Particle p);

void freeWorld(World *world);

void DrawWorld(World *world);

void update(World *world);
