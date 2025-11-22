#include <SDL2/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    // Logical size
    const int WIDTH  = 320;
    const int HEIGHT = 320;

    const int ROWS = 16;
    const int COLS = 16;
    const int TILE_SIZE = 20; // 320 / 16

    // Example matrix (you can change this)
    int matrix[ROWS][COLS] = {
        {0,1,2,3,1,0,2,3,1,0,1,2,3,2,1,0},
        {1,1,2,2,3,3,0,0,1,1,2,3,0,1,2,3},
        {2,2,2,3,3,3,1,1,0,0,3,0,1,2,3,1},
        {3,3,3,0,0,0,2,2,1,1,0,1,2,3,1,2},
        {0,1,2,3,1,0,2,3,1,0,1,2,3,1,2,3},
        {1,1,2,2,3,3,0,0,1,1,2,3,0,1,3,2},
        {2,2,2,3,3,3,1,1,0,0,3,0,1,2,1,0},
        {3,3,3,0,0,0,2,2,1,1,0,1,2,3,2,1},
        {0,1,2,3,1,0,2,3,1,0,1,2,3,2,1,0},
        {1,1,2,2,3,3,0,0,1,1,2,3,0,1,2,3},
        {2,2,2,3,3,3,1,1,0,0,3,0,1,2,3,1},
        {3,3,3,0,0,0,2,2,1,1,0,1,2,3,1,2},
        {0,1,2,3,1,0,2,3,1,0,1,2,3,1,2,3},
        {1,1,2,2,3,3,0,0,1,1,2,3,0,1,3,2},
        {2,2,2,3,3,3,1,1,0,0,3,0,1,2,1,0},
        {3,3,3,0,0,0,2,2,1,1,0,1,2,3,2,1}
    };

    struct Color { Uint8 r, g, b; };
    Color tileColors[] = {
        {0,   0,   0  }, // 0
        {255, 0,   0  }, // 1
        {0,   255, 0  }, // 2
        {0,   0,   255}  // 3
    };

    // Window shows the scaled size (2x)
    SDL_Window* window = SDL_CreateWindow(
        "16x16 Grid",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH * 3,
        HEIGHT * 2,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ✅ Scale everything by 2x
    SDL_RenderSetScale(renderer, 2, 2);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLS; x++) {
                int tileType = matrix[y][x];
                Color c = tileColors[tileType];
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);

                SDL_Rect tile = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_RenderFillRect(renderer, &tile);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

