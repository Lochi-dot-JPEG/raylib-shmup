#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  int windowW = 800;
  int windowH = 600;
  // Create the window and OpenGL context
  InitWindow(windowW, windowH, "Hello Raylib");

  // Utility function from resource_dir.h to find the resources folder and set
  // it as the current working directory so we can load from it
  SearchAndSetResourceDir("resources");

  Texture wabbit = LoadTexture("wabbit_alpha.png");
  Vector2 wabbitSize = {wabbit.width, wabbit.height};

  float wabbitX = 0;
  float wabbitY = 0;
  int wabbitSpeed = 500;

  int currentFps = 60;
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float mouseWheel = GetMouseWheelMove();
    if (mouseWheel != 0) {
      currentFps += (int)mouseWheel;
      if (currentFps < 0)
        currentFps = 0;
      SetTargetFPS(currentFps);
    }
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    // draw some text using the default font
    DrawText("Hello Raylib", 200, 200, 20, WHITE);

    if (IsKeyDown(KEY_D)) {
      wabbitX += wabbitSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) {
      wabbitX -= wabbitSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_W)) {
      wabbitY -= wabbitSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
      wabbitY += wabbitSpeed * GetFrameTime();
    }
    wabbitX = Clamp(wabbitX, 0, windowW - wabbitSize.x);
    wabbitY = Clamp(wabbitY, 0, windowH - wabbitSize.y);

    DrawTexture(wabbit, (int)wabbitX, (int)wabbitY, WHITE);

    EndDrawing();
  }

  UnloadTexture(wabbit);
  CloseWindow();
  return 0;
}
