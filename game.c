#include "include/raylib.h"
#define STB_DS_IMPLEMENTATION
#include "include/stb_ds.h"

#define WIDTH 2560
#define HEIGHT 1440
#define FPS 60
#define STARCOUNT 200

const char *TITLE = "Space Trader";
//windows
//test comment
//test commit22384774
typedef struct {
    Vector2 position;
    int size;
} Star;

void drawStar(Star star) {
    DrawRectangle(star.position.x, star.position.y, star.size, star.size, WHITE);
}

typedef struct {
    Vector2 position;
    float radius;
    char* name;
} Planet;

void drawPlanet(Planet planet) {
    DrawCircle(planet.position.x, planet.position.y, planet.radius, RAYWHITE);
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Star *stars = NULL;

    for (int i = 0; i < STARCOUNT; ++i) {
        Star star = {
            .position = (Vector2){GetRandomValue(0, WIDTH), GetRandomValue(0, HEIGHT)},
            .size = GetRandomValue(1, 6)
        };
        arrput(stars, star);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < arrlen(stars); ++i) {
            drawStar(stars[i]);
        }

        EndDrawing();
    }
    arrfree(stars);

    CloseWindow();
    return 0;
}
