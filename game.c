#include "include/raylib.h"
#define STB_DS_IMPLEMENTATION
#include "include/stb_ds.h"

#define WIDTH 2560
#define HEIGHT 1440
#define FPS 60
#define STARCOUNT 200
#define PLANETCOUNT 5

const char *TITLE = "Space Trader";

const char *planetNames[] = {
    "Juptier",
    "Alagesia",
    "Someplace",
    "Far Away",
    "LOL LOL LOL"
};

typedef struct {
    const char **items;
} Trader;

void printItems(Trader t) {
    if (t.items == NULL) {
        DrawText("No items available", 300, 400, 40, RED);
        return;
    }

    int y = 400; // Initial y position for drawing text
    for (int i = 0; t.items[i] != NULL; i++) {
        DrawText(t.items[i], 300, y, 20, WHITE);
        y += 30; // Increase y position for next item
    }
}

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
    int nameIndex;
} Planet;

void drawPlanet(Planet planet, const char *name) {
    DrawCircle(planet.position.x, planet.position.y, planet.radius, RAYWHITE);
    DrawText(name, planet.position.x - 20, planet.position.y - 60, 15, WHITE);
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

    // Example usage
    Trader trader;
    
    // Initialize the trader struct with some items
    trader.items = (const char *[]){"Item 1", "Item 2", "Item 3", NULL};

    Star *stars = NULL;
    Planet *planets = NULL;

    bool main_menu = true;
    bool planet_menu = false;
    int selectedPlanetIndex = -1;

    for (int i = 0; i < STARCOUNT; ++i) {
        Star star = {
            .position = (Vector2){GetRandomValue(0, WIDTH), GetRandomValue(0, HEIGHT)},
            .size = GetRandomValue(1, 6)
        };
        arrput(stars, star);
    }

    for (int i = 0; i < PLANETCOUNT; ++i) {
        Planet planet = {
            .nameIndex = i,
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
                drawPlanet(planets[i], planetNames[planets[i].nameIndex]);
                if (clickedPlanet(planets[i])) {
                    main_menu = false;
                    planet_menu = true;
                    selectedPlanetIndex = i;
                }
            }

            EndDrawing();
        }

        if (planet_menu) {
            BeginDrawing();
            ClearBackground(BLACK);
            if (selectedPlanetIndex != -1) {
                DrawText(planetNames[planets[selectedPlanetIndex].nameIndex], WIDTH/2-50, 100, 40, WHITE);
                DrawText("Press \"B\" to return to space", WIDTH-250, HEIGHT-100, 15, RED);
                printItems(trader);

                if (IsKeyPressed(KEY_B)) {
                    main_menu = true;
                    planet_menu = false;
                }
            }
            EndDrawing();
        }
    }
    arrfree(stars);
    arrfree(planets);
    CloseWindow();
    return 0;
}
