#include "Core/Random.h"
#include "Core/Time.h"
#include "Math\Vector2.h"
#include "Math\Math.h"
#include "Renderer\Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include <fmod.hpp>
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	//Initialize Engine Systems
	viper::Renderer renderer;
	viper::Time time;

	renderer.Initialize();
	renderer.CreateWindow("Viper Engine", 1280, 1024);

	viper::is input;
	input.Initialize();

	//Create Audio System
	viper::as audio;
	audio.Initialize();

	//Initialize objects



	audio.AddSound("bass.wav", "bass");
	audio.AddSound("snare.wav", "snare");
	audio.AddSound("lag.wav", "lag");
	audio.AddSound("open-hat.wav", "open-hat");

	vector<viper::vec2> points;
	vector<viper::vec2> disco;
	vector<viper::vec2> stars;
	for (int i = 0; i < 100; i++) {
		stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
	}

	SDL_Event e;
	bool quit = false;


	//MAIN LOOP HERE--------------------------------------------------------------------------------------
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		//Update Engine Systems
		input.Update();
		audio.Update();



		if (input.GetKeyPressed(SDL_SCANCODE_Q))
		{
			audio.PlaySound("bass");
		}

		if (input.GetKeyPressed(SDL_SCANCODE_W))
		{
			audio.PlaySound("snare");
		}

		if (input.GetKeyPressed(SDL_SCANCODE_E))
		{
			audio.PlaySound("lag");
		}

		if (input.GetKeyPressed(SDL_SCANCODE_R))
		{
			audio.PlaySound("open-hat");
		}


		//Draw
		//viper::vec3 color{ 1, 0, 0 };
		renderer.SetColor(0,0,0);
		renderer.Clear();

		/*Creating Stars
		viper::vec2 speed{ 140.0f, 0.0f };
		float length = speed.Length();

		for (auto& star : stars) {
			star += speed * time.GetDeltaTime();

			if (star[0] > 1280)  star[0] = 0;
			if (star[0] < 0)  star[0] = 1280;

			renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);
			renderer.DrawPoint(star.x, star.y);
			renderer.Present(); // Render the screen
		}
		for (int i = 0; i < (int)points.size() - 1; i++) {
			// set color or random color
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		for (int i = 0; i < (int)points.size() - 1; i++) {
			// set color or random color
			renderer.SetColor((uint8_t)viper::random::getRandomInt(255), viper::random::getRandomInt(255), viper::random::getRandomInt(255), viper::random::getRandomInt(255));
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}
		*/
		/*       Code for Disco Lights
		for (auto& lights : disco) {
			  renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);
			  renderer.DrawLine(viper::random::getRandomInt(1280), viper::random::getRandomInt(1024), viper::random::getRandomInt(1280), viper::random::getRandomInt(1024));
		}
	 */
		renderer.Present();

	}
	input.Shutdown();
	audio.Shutdown();
}

