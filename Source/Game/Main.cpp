#include "\Users\sombr\Neumont College Of Computer Science\Year II\Summer\Sprint I\C++ Programming II\Cpp_II\Source\Engine\Core\Random.h"
#include "\Users\sombr\Neumont College Of Computer Science\Year II\Summer\Sprint I\C++ Programming II\Cpp_II\Source\Engine\Math\Vector2.h"
#include "\Users\sombr\Neumont College Of Computer Science\Year II\Summer\Sprint I\C++ Programming II\Cpp_II\Source\Engine\Math\Math.h"
#include "\Users\sombr\Neumont College Of Computer Science\Year II\Summer\Sprint I\C++ Programming II\Cpp_II\Source\Engine\Renderer\Renderer.h"

#include "Core/Time.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
using namespace std;

    int main(int argc, char* argv[]) {
        viper::Renderer renderer;
        viper::Time time;

        renderer.Initialize();
        renderer.CreateWindow("Viper Engine", 1280, 1024);
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Event e;
        bool quit = false;

        vector<vec2> stars;
        for (int i = 0; i < 100; i++) {
            stars.pushback(vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
            
        }

        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }


            renderer.SetColor(0, 0, 0);
            renderer.Clear();


            viper::vec2 speed{ -140.0f, 0.0f };
            float length = speed.Length();


            for (auto& star : stars) {
                star += speed * time.GetDeltaTime();

                if (star[0] > 1280) star[0] = 0;
                if (star[0] < 0) star[0] = 1280;

                renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);
                renderer.DrawPoint(star.x, star.y);
            }





        }
    /*
        // Define a rectangle
        SDL_FRect greenSquare{ 270, 190, 200, 200 };

  
            SDL_SetColor(renderer, getRandomInt(256), getRandomInt(256), getRandomInt(256), 255); // Set render draw color to black
            Set.Draline(viper
            SDL_RenderClear(renderer); // Clear the renderer

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
            SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

            SDL_RenderPresent(renderer); // Render the screen
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
        */
    }

