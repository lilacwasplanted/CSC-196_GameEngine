#include "Core/Random.h"
#include "Core/Time.h"
#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include "Math\Math.h"
#include "Renderer\Renderer.h"
#include "Renderer\Model.h"
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

	vector<viper::vec2> verts{
	{-4, 1 },
	{ 4, 1 },
	{-3, -4 },
	{0, 4 },
	{3, -4 },
	{-4, 1},

	};

	viper::Model model;


	//Initialize Sounds
	audio.AddSound("bass.wav", "bass");
	audio.AddSound("snare.wav", "snare");
	audio.AddSound("lag.wav", "lag");
	audio.AddSound("open-hat.wav", "open-hat");

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
		
		if (input.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

		//Update Engine Systems
		input.Update();
		audio.Update();

		if (input.GetKeyPressed(SDL_SCANCODE_Q))audio.PlaySound("bass");
		if (input.GetKeyPressed(SDL_SCANCODE_W))audio.PlaySound("snare");
		if (input.GetKeyPressed(SDL_SCANCODE_E))audio.PlaySound("open-hat");
		if (input.GetKeyPressed(SDL_SCANCODE_R))audio.PlaySound("lag");

		//Draw
		viper::vec3 color{ 0, 0, 0 };

		renderer.SetColor(color.r, color.g, color.b);
		renderer.Clear();

		model.Draw(renderer, input.GetMousePos(), time.GetTime(), 10.0f);

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

	}
	input.Shutdown();
	audio.Shutdown();
}

