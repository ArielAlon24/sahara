#define RAYLIB_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

#include "particle.h"
#include "raylib.h"
#include "world.h"

#define WIDTH 800
#define HEIGHT 450
#define PARTICLE_SIZE 10
#define FPS 60

int main(void) {
  World *world =
      initWorld(WIDTH / PARTICLE_SIZE, HEIGHT / PARTICLE_SIZE, PARTICLE_SIZE);

  for (int i = 10; i < 22; i++) {
    for (int j = 2; j < 12; j++) {
      setParticle(world, i, j, PARTICLE_SAND);
    }
  }

  InitWindow(WIDTH, HEIGHT, "sand");
  SetTargetFPS(FPS);

  Vector2 mousePosition;
  Particle currentParticle = PARTICLE_SAND;

  while (!WindowShouldClose()) {
    mousePosition = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      int x = (int)mousePosition.x / PARTICLE_SIZE;
      int y = (int)mousePosition.y / PARTICLE_SIZE;
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          setParticle(world, x + i, y + j, currentParticle);
        }
      }
    }

    BeginDrawing();

    update(world);

    DrawWorld(world);
    EndDrawing();
  }

  freeWorld(world);
  CloseWindow();

  return 0;
}
