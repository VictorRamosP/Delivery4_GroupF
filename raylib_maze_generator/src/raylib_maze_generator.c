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

#include <stdlib.h>             // Required for: malloc(), free()

#define MAZE_WIDTH      32
#define MAZE_HEIGHT     32
#define MAZE_SCALE      10

// Define new data type: Point
typedef struct Point {
    int x;
    int y;
} Point;

// Declare function to be used in main(), definition is placed after main()
static Image GenImageMaze(int width, int height, int spacingRows, int spacingCols, float pointChance);

bool CheckCollisionWithMaze(Image imMaze, Rectangle player, Vector2 offset);

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

    // Define a random seed for maze generation
    int seed = 37867;
    SetRandomSeed(seed);

    // Generate maze image using provided function
    Image imMaze = GenImageMaze(MAZE_WIDTH, MAZE_HEIGHT, 4, 4, 0.5f);

    // Load a texture from our image data, to be drawn on screen
    Texture2D texMaze = LoadTextureFromImage(imMaze);

    // Define map position (considering scale)
    Vector2 position = {
        screenWidth / 2 - imMaze.width * MAZE_SCALE / 2,
        screenHeight / 2 - imMaze.height * MAZE_SCALE / 2
    };


    // Load one texture to apply to maze walls and floor
    //Texture2D texture = LoadTexture("../../../resources/maze_atlas04.png");
    int textureIndex = 4;
    char texturePath[50];
    sprintf(texturePath, "../../../resources/maze_atlas0%d.png", textureIndex);
    Texture2D texture = LoadTexture(texturePath);

    // Define player position and size
    Rectangle player = { position.x + 1 * MAZE_SCALE + 2, position.y + 1 * MAZE_SCALE + 2, 4, 4 };

    // Define 2D camera to transform our world accordingly (translate, scale)
    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 2, player.y + 2 };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 10.0f;

    bool mode = 1;      // 0-Editor, 1-Game

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Reset maze for new random generation
        if (IsKeyPressed(KEY_R))
        {
            // Set a new seed and re-generate maze
            seed += 11;
            UnloadImage(imMaze);
            UnloadTexture(texMaze);
            imMaze = GenImageMaze(MAZE_WIDTH, MAZE_HEIGHT, 4, 4, 0.5f);
            texMaze = LoadTextureFromImage(imMaze);

            
        }
        if (IsKeyPressed(KEY_ONE))
        {
            textureIndex = 1;
            sprintf(texturePath, "../../../resources/maze_atlas0%d.png", textureIndex);
            texture = LoadTexture(texturePath);
        }else if (IsKeyPressed(KEY_TWO))
        {
            textureIndex = 2;
            sprintf(texturePath, "../../../resources/maze_atlas0%d.png", textureIndex);
            texture = LoadTexture(texturePath);
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            textureIndex = 3;
            sprintf(texturePath, "../../../resources/maze_atlas0%d.png", textureIndex);
            texture = LoadTexture(texturePath);
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            textureIndex = 4;
            sprintf(texturePath, "../../../resources/maze_atlas0%d.png", textureIndex);
            texture = LoadTexture(texturePath);
        }
        // Change mode: 0-Editor, 1-Game
        if (IsKeyPressed(KEY_SPACE)) mode = !mode;

        if (mode == 0)  // Editor mode
        {
            // Map edition with mouse
            // NOTE: We must translate mouse coordinates to maze image coordinates
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                Vector2 mousePos = GetMousePosition();

                if ((mousePos.x >= position.x) && (mousePos.y >= position.y))
                {
                    Point mapCoord = {
                        (int)((mousePos.x - position.x) / MAZE_SCALE),
                        (int)((mousePos.y - position.y) / MAZE_SCALE),
                    };

                    ImageDrawPixel(&imMaze, mapCoord.x, mapCoord.y, GREEN);

                    UnloadTexture(texMaze);
                    texMaze = LoadTextureFromImage(imMaze);
                }
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                Vector2 mousePos = GetMousePosition();

                if ((mousePos.x >= position.x) && (mousePos.y >= position.y))
                {
                    Point mapCoord = {
                        (int)((mousePos.x - position.x) / MAZE_SCALE),
                        (int)((mousePos.y - position.y) / MAZE_SCALE),
                    };

                    ImageDrawPixel(&imMaze, mapCoord.x, mapCoord.y, WHITE);

                    UnloadTexture(texMaze);
                    texMaze = LoadTextureFromImage(imMaze);
                }
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                Vector2 mousePos = GetMousePosition();

                if ((mousePos.x >= position.x) && (mousePos.y >= position.y))
                {
                    Point mapCoord = {
                        (int)((mousePos.x - position.x) / MAZE_SCALE),
                        (int)((mousePos.y - position.y) / MAZE_SCALE),
                    };

                    ImageDrawPixel(&imMaze, mapCoord.x, mapCoord.y, BLACK);

                    UnloadTexture(texMaze);
                    texMaze = LoadTextureFromImage(imMaze);
                }
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
            {
                Vector2 mousePos = GetMousePosition();

                if ((mousePos.x >= position.x) && (mousePos.y >= position.y))
                {
                    Point mapCoord = {
                        (int)((mousePos.x - position.x) / MAZE_SCALE),
                        (int)((mousePos.y - position.y) / MAZE_SCALE),
                    };

                    ImageDrawPixel(&imMaze, mapCoord.x, mapCoord.y, RED);

                    UnloadTexture(texMaze);
                    texMaze = LoadTextureFromImage(imMaze);
                }
            }
        }
        else  // Game mode
        {

            Rectangle oldPlayer = player; // Position player before collision
            // Player movement
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += 2;
            else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= 2;
            else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) player.y += 2;
            else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) player.y -= 2;

            if (CheckCollisionWithMaze(imMaze, player, position))
            {
                player = oldPlayer; // Revertimos el movimiento si hay colisión
            }
            // Update camera target position with new player position
            camera.target = (Vector2){ player.x + 2, player.y + 2 };
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);

        if (mode == 0) // Editor
        {
            // Draw the map image in the middle of the screen
            DrawTextureEx(texMaze, position, 0.0f, MAZE_SCALE, WHITE);
        }
        else // Game
        {
            // Enable Camera to apply transformation (position, scale)
            // to maze drawing using current texture
            BeginMode2D(camera);

            // For each pixel in the image, draw a rectangle piece of the texture 
            // at specific coordinates with specific size
            for (int y = 0; y < imMaze.height; y++)
            {
                for (int x = 0; x < imMaze.width; x++)
                {
                    if (ColorIsEqual(GetImageColor(imMaze, x, y), WHITE))
                    {
                        DrawTexturePro(texture, (Rectangle) { 0, texture.height / 2, texture.width / 2, texture.height / 2 },
                            (Rectangle) {
                            position.x + x * MAZE_SCALE, position.y + y * MAZE_SCALE, MAZE_SCALE, MAZE_SCALE
                        },
                            (Vector2) {
                            0
                        }, 0.0f, WHITE);
                    }
                    else
                    {
                        DrawTexturePro(texture, (Rectangle) { texture.width / 2, texture.height / 2, texture.width / 2, texture.height / 2 },
                            (Rectangle) {
                            position.x + x * MAZE_SCALE, position.y + y * MAZE_SCALE, MAZE_SCALE, MAZE_SCALE
                        },
                            (Vector2) {
                            0
                        }, 0.0f, WHITE);
                    }
                }
            }
            
            // Draw player
            DrawRectangleRec(player, RED);

            EndMode2D();
        }

        // Draw required UI info
        DrawText("[R] GENERATE NEW RANDOM SEQUENCE", 10, 36, 10, LIGHTGRAY);

        DrawText(TextFormat("SEED: %i", seed), 10, 56, 10, YELLOW);

        DrawText("[SPACE] TOGGLE MODE: EDITOR/GAME", 10, GetScreenHeight() - 20, 10, WHITE);

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload all loaded resources
    UnloadImage(imMaze);
    UnloadTexture(texMaze);
    UnloadTexture(texture);

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
bool CheckCollisionWithMaze(Image imMaze, Rectangle player, Vector2 offset)
{
    for (int y = (int)player.y; y < (int)(player.y + player.height); y++)
    {
        for (int x = (int)player.x; x < (int)(player.x + player.width); x++)
        {
            int mapX = (x - (int)offset.x) / MAZE_SCALE;
            int mapY = (y - (int)offset.y) / MAZE_SCALE;

            if (mapX >= 0 && mapX < imMaze.width && mapY >= 0 && mapY < imMaze.height)
            {
                if (ColorIsEqual(GetImageColor(imMaze, mapX, mapY), WHITE))
                {
                    return true; // Collision detected
                }
            }
        }
    }
    return false;
}
// Generate procedural maze image, using grid-based algorithm
// NOTE: Color scheme used: WHITE = Wall, BLACK = Walkable
Image GenImageMaze(int width, int height, int spacingRows, int spacingCols, float pointChance)
{
    Image imMaze = { 0 };

    // STEP 1: Generate empty image with borders
    //---------------------------------------------------------------------------------
    // STEP 1.1: Generate image of plain color
    imMaze = GenImageColor(width, height, BLACK);

    // STEP 1.2: Draw image border
    for (int y = 0; y < imMaze.height; y++)
    {
        for (int x = 0; x < imMaze.width; x++)
        {
            if ((x == 0) || (x == (imMaze.width - 1)) ||
                (y == 0) || (y == (imMaze.height - 1)))
            {
                ImageDrawPixel(&imMaze, x, y, WHITE);
            }
        }
    }
    //---------------------------------------------------------------------------------

    // STEP 2: Set some random point in image at specific row-column distances
    //---------------------------------------------------------------------------------
    // STEP 2.1: Define an array of point used for maze generation
    // NOTE A: Static array allocation, memory allocated in STACK (MAX: 1MB)
    // NOTE B: Dynamic array allocation, memory allocated in HEAP (MAX: Available RAM)
    //Point mazePoints[64] = { 0 }; // Static array
    Point* mazePoints = malloc(256 * sizeof(Point)); // Dynamic array (MAX: 256 points)
    int mazePointCounter = 0;

    // STEP 2.2: Store specific points, at specific row-column distances
    for (int y = 0; y < imMaze.height; y++)
    {
        for (int x = 0; x < imMaze.width; x++)
        {
            if ((x != 0) && (x != (imMaze.width - 1)) &&
                (y != 0) && (y != (imMaze.height - 1)))
            {
                if ((x % spacingCols == 0) && (y % spacingRows == 0))
                {
                    if (GetRandomValue(0, 100) <= (int)(pointChance * 100))
                    {
                        mazePoints[mazePointCounter] = (Point){ x, y };
                        mazePointCounter++;
                    }
                }
            }
        }
    }

    // STEP 2.3: Draw our points in image
    for (int i = 0; i < mazePointCounter; i++)
    {
        ImageDrawPixel(&imMaze, mazePoints[i].x, mazePoints[i].y, WHITE);
    }
    //---------------------------------------------------------------------------------

    // STEP 3: Draw lines from every point in a random direction
    //---------------------------------------------------------------------------------
    // STEP 3.1: Define an array of 4 directions for convenience
    Point directions[4] = {
        { 1, 0 },   // East
        { -1, 0 },  // West
        { 0, 1 },   // South
        { 0, -1 },  // North
    };

    // STEP 3.2: Load a random sequence of points, to be used as indices, so,
    // we can access maze-points randomly indexed, instead of following the order we stored them
    int* pointOrder = LoadRandomSequence(mazePointCounter, 0, mazePointCounter - 1);

    // STEP 3.3: Process every random maze point, drawing pixels in one random direction,
    // until we collision with another wall (WHITE pixel)
    for (int i = 0; i < mazePointCounter; i++)
    {
        Point currentPoint = mazePoints[pointOrder[i]];
        Point currentDir = directions[GetRandomValue(0, 3)];
        Point nextPoint = { currentPoint.x + currentDir.x, currentPoint.y + currentDir.y };

        while (ColorIsEqual(GetImageColor(imMaze, nextPoint.x, nextPoint.y), BLACK))
        {
            ImageDrawPixel(&imMaze, nextPoint.x, nextPoint.y, WHITE);

            nextPoint.x += currentDir.x;
            nextPoint.y += currentDir.y;
        }
    }

    // If using dynamic memory allocation for mazePoints,
    // they allocated memory must be manually freed 
    free(mazePoints);

    // Free pointOrder array, allocated internally by LoadRandomSequence()
    UnloadRandomSequence(pointOrder);
    //-----------------------------------------------------------------------------------

    return imMaze;
}
