#include "include/raylib.h"
#define STB_DS_IMPLEMENTATION
#include "include/stb_ds.h"

#define WIDTH 2560
#define HEIGHT 1440
#define FPS 60
#define STARCOUNT 200
#define PLANETCOUNT 5

const char *TITLE = "Space Trader";

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
    const char* name;
} Planet;

void drawPlanet(Planet planet) {
    DrawCircle(planet.position.x, planet.position.y, planet.radius, RAYWHITE);
    DrawText(planet.name, planet.position.x - 20, planet.position.y - 50, 15, WHITE);
}

bool clickedPlanet(Planet planet) {
    Vector2 mouse_pos = GetMousePosition();

    if (CheckCollisionPointCircle(mouse_pos, planet.position, planet.radius)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return true;
        }
    }
    return false;
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Star *stars = NULL;
    Planet *planets = NULL;

    bool main_menu = true;
    bool planet_menu = false;

    for (int i = 0; i < STARCOUNT; ++i) {
        Star star = {
            .position = (Vector2){GetRandomValue(0, WIDTH), GetRandomValue(0, HEIGHT)},
            .size = GetRandomValue(1, 6)
        };
        arrput(stars, star);
    }

    for (int i = 0; i < PLANETCOUNT; ++i) {
        Planet planet = {
            .name = "Planet",
            .position = (Vector2){GetRandomValue(0, WIDTH), GetRandomValue(0, HEIGHT)},
            .radius = GetRandomValue(20, 50)
        };
        arrput(planets, planet);
    }

    while (!WindowShouldClose()) {
        if (main_menu) {
            BeginDrawing();
            ClearBackground(BLACK);

            for (int i = 0; i < arrlen(stars); ++i) {
                drawStar(stars[i]);
            }

            for (int i = 0; i < arrlen(planets); ++i) {
                drawPlanet(planets[i]);
                if (clickedPlanet(planets[i])) {
                    main_menu = false;
                    planet_menu = true;
                }
            }

            EndDrawing();
        }

        if (planet_menu) {
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
        }
    }
    arrfree(stars);
    arrfree(planets);
    CloseWindow();
    return 0;
}
