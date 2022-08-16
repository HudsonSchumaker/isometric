
#include <map>
#include <array>     // std::array
#include <math.h>
#include <vector>
#include <random>    // std::default_random_engine
#include <chrono>
#include <thread>
#include <future>
#include <string>
#include <utility>   // std:pair<T, T>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <algorithm> // std::shuffle
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>

constexpr static float FPS = 144.0f;
constexpr static float MILLISECS_PER_FRAME = 1000.0f / FPS;
static const int WIDTH = 800;
static const int H_WIDTH = WIDTH / 2;
static const int HEIGHT = 600;
//static const int H_HEIGHT = HEIGHT / 2;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* tileImages[4];

bool isRunning = false;
int millisecsPreviousFrame = 0;
double deltaTime = 0.0;
int tileW = 0;
int tileH = 0;
int startX = 0;
int startY = 0;

void setUp();
void input();
void update();
void render(SDL_Texture* img, int x, int y);
void loop();
void quit();

int main(int argc, char *argv[]) {
    setUp();
    loop();
    quit();
    return 0;
}

void loop() {
    isRunning = true;
    int timeToWait = 0;

    while (isRunning) {
        timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
        if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
            SDL_Delay(timeToWait);
        }
        deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
        millisecsPreviousFrame = SDL_GetTicks();

        input();
        update();
    }
}

void input() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                isRunning = false;
                // exit(0);
            break;
            
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_SPACE) {
                    isRunning = false;
                }
            break;
        }
    }
}

void update() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render(tileImages[0], 0, 0);
    render(tileImages[0], 1, 0);
    render(tileImages[0], 2, 0);
    render(tileImages[0], 0, 1);
    render(tileImages[0], 1, 1);
    render(tileImages[0], 2, 1);
    render(tileImages[0], 0, 2);
    render(tileImages[0], 1, 2);
    render(tileImages[0], 2, 2);
render(tileImages[0], 3, 0);
    render(tileImages[0], 4, 0);
    render(tileImages[0], 4, 1);
    render(tileImages[0], 4, 2);

    SDL_RenderPresent(renderer);  
}

void render(SDL_Texture* img, int x, int y) {

    int screenX = startX + (x - y) * tileW/2;
    int screenY = startY + (x + y) * tileH/2.32;


    SDL_Rect rect = { screenX, screenY, tileW, tileH };
    SDL_RenderCopy(renderer, img, NULL, &rect);  
}

void setUp() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow(
        "Isometric", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_METAL 
    );
    
    SDL_Surface* iconSurface = IMG_Load("data/joypad.png");
    SDL_SetWindowIcon(window, iconSurface);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);   
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 256);

    SDL_Surface* grassSurface = IMG_Load("data/grass.png");
    SDL_Texture* grass = SDL_CreateTextureFromSurface(renderer, grassSurface);

    SDL_Surface* sandSurface = IMG_Load("data/sand.png");
    SDL_Texture* sand = SDL_CreateTextureFromSurface(renderer, sandSurface);

    SDL_Surface* waterSurface = IMG_Load("data/water.png");
    SDL_Texture* water = SDL_CreateTextureFromSurface(renderer, waterSurface);

    SDL_Surface* voxelSurface = IMG_Load("data/voxelTile_08.png");
    SDL_Texture* voxel = SDL_CreateTextureFromSurface(renderer, voxelSurface);


    
    tileImages[0] = grass;
    tileImages[1] = sand;
    tileImages[2] = water;
    tileImages[3] = voxel;

    SDL_Point size;
    SDL_QueryTexture(tileImages[0], NULL, NULL, &size.x, &size.y);
    tileW = size.x;
    tileH = size.y;
    startX = H_WIDTH - (tileW/2);
    startY = 50;

    SDL_FreeSurface(grassSurface);
    SDL_FreeSurface(sandSurface);
    SDL_FreeSurface(waterSurface);
    SDL_FreeSurface(voxelSurface);
}

void quit() {
    SDL_Quit();
    IMG_Quit();
	TTF_Quit();
    Mix_Quit();
}
