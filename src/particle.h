#ifndef PARTICLES_H
#define PARTICLES_H

#include "raylib.h"

typedef enum {
  PARTICLE_AIR = 0,
  PARTICLE_SAND = 1,
} Particle;

Color getColor(Particle p);

#endif  // PARTICLES_H
