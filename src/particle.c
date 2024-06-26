#include <stdlib.h>

#include "raylib.h"

typedef enum {
  PARTICLE_AIR = 0,
  PARTICLE_SAND = 1,
} Particle;

Color getColor(Particle p) {
  switch (p) {
    case PARTICLE_AIR:
      return BLACK;
    case PARTICLE_SAND:
      return YELLOW;
    default:
      return BLACK;
  }
}
