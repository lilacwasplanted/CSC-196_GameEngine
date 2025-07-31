#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Core/Random.h"
#include "Game/Actor.h"
#include "Math/Math.h"
#include "Core/Time.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <fmod.hpp>
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
	{-4, 1}
	};

	viper::Model* model = new viper::Model{ verts,{255,255,255} };
	viper::Transform transform{ viper::vec2{640, 512}, 0, 20.0f };

	viper::Actor actor{ transform, model };

	vector<viper::vec2> stars;
	for (int i = 0; i < 100; i++) {
		stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
	}

	Font* font = new Font();
	font->Load("Farmshow.ttf", 80);

	Text* text = new Text(font);
	text->Create(renderer, "Chihiro", viper::vec3{1,1,1});


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


		float speed = 200.0f;
		viper::vec2 direction{ 0, 0 };
		

		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation -= viper::math::degToRad( 90 * time.GetDeltaTime()); 	
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += viper::math::degToRad( 90 * time.GetDeltaTime()); 	

		if (input.GetKeyDown(SDL_SCANCODE_W))direction.y = -1; // speed * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1; // speed * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1; // speed * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1; // speed * time.GetDeltaTime();

		if (direction.LengthSqr() > 0) {
		direction = direction.Normalized();
		actor.GetTransform().pos += (direction * speed) * time.GetDeltaTime();
		}
		//Draw
		viper::vec3 color{ 0, 0, 0 };

		renderer.SetColor(color.r, color.g, color.b);			//Background color
		renderer.Clear();
		
		//model.Draw(renderer,input.GetMousePos(), 5.0f, 25.0f); // Draw the model at the center of the screen
		//model.Draw(renderer, transform); // Draw the model using a transform
		actor.Draw(renderer); // Draw the actor

		text->Draw(renderer, 40.0f, 40.0f);


		viper::vec2 sped{ 140.0f, 0.0f };
		float length = sped.Length();

		for (auto& star : stars) {
			star += sped * time.GetDeltaTime();

			if (star[0] > 1280)  star[0] = 0;
			if (star[0] < 0)  star[0] = 1280;

			renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);
			renderer.DrawPoint(star.x, star.y);
		}

			renderer.Present(); // Render the screen
	}
	input.Shutdown();
	audio.Shutdown();
}

