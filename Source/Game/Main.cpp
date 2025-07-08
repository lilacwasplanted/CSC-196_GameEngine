#include "Core\Random.h"
#include "Math\Vector2.h"
#include "Math\Math.h"
#include "Renderer\Renderer.h"

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

        vector<viper::vec2> disco;
        vector<viper::vec2> stars;
        for (int i = 0; i < 100; i++) {
            stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
            disco.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
            
        }


        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }


            renderer.SetColor(0, 0, 0);
            renderer.Clear();


            viper::vec2 speed{ 140.0f, 0.0f };
            float length = speed.Length();


            for (auto& star : stars) {
                star += speed * time.GetDeltaTime();

                if (star[0] > 1280)  star[0] = 0; 
                if (star[0] < 0)  star[0] = 1280; 

                renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);
                renderer.DrawPoint(star.x, star.y);
            }



            for (auto& lights : disco) {


                renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);

                renderer.DrawLine(viper::random::getRandomInt(1280), viper::random::getRandomInt(1024), viper::random::getRandomInt(1280), viper::random::getRandomInt(1024));
                renderer.Present(); // Render the screen


            }

        }
    }

