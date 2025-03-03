/*******************************************************************************************
*
*   raylib maze generator
*
*   Procedural maze generator using Maze Grid Algorithm
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2024-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>                     // Required for: malloc(), free()
typedef struct Point {
    int x;
    int y;
}Point;
//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib maze generator");


    //modo editor (esta puesto a parte de todo la logica esta)
    // 
   /* if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousPo = GetMousePosition();

        if ((mousPo.x >= position.x) && (mousPo.y >= position.y)) {
           
            Point maoCoord = {
                (int)((mousPo.x - position.x)) / MAZE_SCALE),
                (int)((mousPo.y - position.y)) / MAZE_SCALE)
            };
            ImageDrawPixel(&imMaze, mapCoord.x, mapCoord.y, WHITE);

            UnloadTexture(textMaze);
            textMaze = LoadTextureFromImage(ImMaze)
        }
    }
   */
    // TODO: Define a random seed for maze generation
    
    // Maze generation algorithm implementation
    //-----------------------------------------------------------------------------------
    // STEP 1: Generate empty image with borders
    
    // TODO 1.1: Generate image of plain color
    
    // TODO 1.2: Draw image border
    
    // STEP 2: Set some random point in image at specific row-column distances

    // TODO 2.1: Define an array of point used for maze generation
    // NOTE A: Static array allocation, memory allocated in STACK (MAX: 1MB)
    // NOTE B: Dynamic array allocation, memory allocated in HEAP (MAX: Available RAM)
     
    // TODO 2.2: Store specific points, at specific row-column distances

    // TODO 2.3: Draw our points in image

    // STEP 3: Draw lines from every point in a random direction

    // TODO 3.1: Define an array of 4 directions for convenience

    // TODO 3.2: Load a random sequence of points, to be used as indices, so,
    // we can access maze-points randomly indexed, instead of following the order we stored them

    // TODO 3.3: Process every random maze point, drawing pixels in one random direction,
    // until we collision with another wall (WHITE pixel)
    //-----------------------------------------------------------------------------------

    // TODO: Load a texture from our image data, to be drawn on screen

    SetTargetFPS(30);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Reset maze for new random generation
        if (IsKeyPressed(KEY_R))
        {
            // TODO: Reset all required variables for maze regeneration
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // TODO: Draw generated maze texture, scaled and centered on screen

            // TODO: Draw lines rectangle over texture, scaled and centered on screen

            // Draw required UI info
            DrawText("[R] GENERATE NEW RANDOM SEQUENCE", 10, 36, 10, GRAY);
            
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // TODO: Unload all loaded resources

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// TODO: Generate maze image, using a pre-defined function
// NOTE: All image maze generation code could be contained in this function
static Image GenImageMaze(int width, int height, float pointChance)
{
    Image imMaze = { 0 };

    // TODO: Generate procedural maze image, using grid-based algorithm
    // NOTE: Color scheme used: WHITE = Wall, BLACK = Walkable

    return imMaze;
}
