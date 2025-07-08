#include <iostream>
#include "Math/Math.h"
#include "Renderer/Renderer.h"
#include <SDL3/SDL.h>
using namespace std;

    int main(int argc, char* argv[]) {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Window* window  = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
        if (window == nullptr) {
            cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
            SDL_Quit();
            return 1;
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == nullptr) {
            cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        SDL_Event e;
        bool quit = false;

        // Define a rectangle
        SDL_FRect greenSquare{ 270, 190, 200, 200 };

        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
            SDL_RenderClear(renderer); // Clear the renderer

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
            SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

            SDL_RenderPresent(renderer); // Render the screen
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }

