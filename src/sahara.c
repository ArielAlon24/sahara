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

typedef struct {
    ParticleType type;
    int length;
} Cursor;

Cursor *init_cursor(void) {
    Cursor *c = (Cursor *)malloc(sizeof(Cursor));
    if (c == NULL) {
        return NULL;
    }
    c->type = SAND;
    c->length = 1;
    return c;
}

void free_cursor(Cursor *cursor) { free(cursor); }

void adjust_cursor_length(Cursor *cursor, int mouse_wheel_move) {
    size_t new_length = cursor->length + mouse_wheel_move;
    if (new_length <= 1) {
        cursor->length = 1;
    } else if (new_length >= WIDTH / 4) {
        cursor->length = WIDTH / 4;
    } else {
        cursor->length = new_length;
    }
}

void draw_cursor(Cursor *cursor, size_t x, size_t y) {
    // xP + 1 - (size / 2)P = P(x - size / 2) + 1
    DrawRectangleLines(PARTICLE_SIZE * (x - cursor->length / 2) + 1,
                       PARTICLE_SIZE * (y - cursor->length / 2) + 1,
                       PARTICLE_SIZE * cursor->length - 1, PARTICLE_SIZE * cursor->length - 1,
                       particle_type_color(cursor->type));
}

void set_area_particle_type(World *world, int x, int y, int length, ParticleType current_type) {
    int half_length = length / 2;
    int start_offset = x - half_length >= 0 ? -half_length : 0;
    int end_offset = (length % 2 == 0) ? half_length - 1 : half_length;

    for (int dx = x - half_length >= 0 ? -half_length : 0; dx <= end_offset; dx++) {
        for (int dy = y - half_length >= 0 ? -half_length : 0; dy <= end_offset; dy++) {
            set_particle_type(world, x + dx, y + dy, current_type);
        }
    }
}

Vector2 get_mouse_particle_position(void) {
    Vector2 position = GetMousePosition();
    Vector2 particle_position = {(size_t)position.x / PARTICLE_SIZE,
                                 (size_t)position.y / PARTICLE_SIZE};
    return particle_position;
}

int main(void) {
    World *world =
        init_world(WIDTH / PARTICLE_SIZE, HEIGHT / PARTICLE_SIZE, PARTICLE_SIZE, G_FORCE);

    InitWindow(WIDTH, HEIGHT, NAME);
    SetTargetFPS(FPS);
    Cursor *cursor = init_cursor();

    Vector2 mouse_position;

    while (!WindowShouldClose()) {

        mouse_position = GetMousePosition();

        size_t x = (size_t)mouse_position.x / PARTICLE_SIZE;
        size_t y = (size_t)mouse_position.y / PARTICLE_SIZE;
        adjust_cursor_length(cursor, (int)GetMouseWheelMove());

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            set_area_particle_type(world, x, y, cursor->length, cursor->type);
        }

        if (IsKeyDown(KEY_ONE)) {
            cursor->type = SAND;
        }

        if (IsKeyDown(KEY_TWO)) {
            cursor->type = STONE;
        }

        if (IsKeyDown(KEY_THREE)) {
            cursor->type = AIR;
        }

        if (IsKeyDown(KEY_R)) {
            reset_world(world);
        }

        BeginDrawing();

        update(world);
        draw_world(world);
        draw_cursor(cursor, x, y);

        EndDrawing();
    }

    free_world(world);
    free_cursor(cursor);
    CloseWindow();

    return 0;
}
