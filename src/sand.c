#define RAYLIB_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

#include "particle.h"
#include "raylib.h"
#include "world.h"

#define NAME "sand"
#define WIDTH 800
#define HEIGHT 800
#define PARTICLE_SIZE 2
#define FPS 60
#define G_FORCE 0.2

void draw_cursor(size_t x, size_t y, size_t length, Color color) {
    // xP + 1 - (size / 2)P = P(x - size / 2) + 1
    DrawRectangleLines(PARTICLE_SIZE * (x - length / 2) + 1, PARTICLE_SIZE * (y - length / 2) + 1,
                       PARTICLE_SIZE * length - 1, PARTICLE_SIZE * length - 1, color);
}

void set_area_particle_type(World *world, int x, int y, int length, ParticleType current_type) {
    int half_length = length / 2;
    int start_offset = -half_length;
    int end_offset = (length % 2 == 0) ? half_length - 1 : half_length;

    for (int i = start_offset; i <= end_offset; i++) {
        for (int j = start_offset; j <= end_offset; j++) {
            set_particle_type(world, x + i, y + j, current_type);
        }
    }
}

int adjust_length(int length, int mouse_wheel_move) {
    int new_length = length + mouse_wheel_move;
    if (new_length <= 1) {
        return 1;
    }

    if (new_length >= WIDTH / PARTICLE_SIZE) {
        return WIDTH / PARTICLE_SIZE;
    }

    return new_length;
}

int main(void) {
    World *world =
        init_world(WIDTH / PARTICLE_SIZE, HEIGHT / PARTICLE_SIZE, PARTICLE_SIZE, G_FORCE);

    InitWindow(WIDTH, HEIGHT, NAME);
    SetTargetFPS(FPS);

    Vector2 mouse_position;
    ParticleType current_type = SAND;
    int length = 1;

    while (!WindowShouldClose()) {
        mouse_position = GetMousePosition();
        size_t x = (size_t)mouse_position.x / PARTICLE_SIZE;
        size_t y = (size_t)mouse_position.y / PARTICLE_SIZE;

        int mouse_wheel_move = (int)GetMouseWheelMove();
        length = adjust_length(length, mouse_wheel_move);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            set_area_particle_type(world, x, y, length, current_type);
        }

        if (IsKeyDown(KEY_ONE)) {
            current_type = SAND;
        }

        if (IsKeyDown(KEY_TWO)) {
            current_type = STONE;
        }

        if (IsKeyDown(KEY_THREE)) {
            current_type = AIR;
        }

        if (IsKeyDown(KEY_R)) {
            reset_world(world);
        }

        BeginDrawing();

        update(world);

        draw_world(world);
        draw_cursor(x, y, length, particle_type_color(current_type));

        EndDrawing();
    }

    free_world(world);
    CloseWindow();

    return 0;
}
