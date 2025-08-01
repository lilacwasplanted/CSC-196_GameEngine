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

#include "Game/Player.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <fmod.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <string>


using namespace std;

int main(int argc, char* argv[]) {


	//Initialize Engine Systems
	viper::Time time;

	unique_ptr<viper::Renderer> renderer = make_unique<viper::Renderer>();
	unique_ptr<viper::as> audio = make_unique<viper::as>();
	unique_ptr<viper::is> input = make_unique<viper::is>();

	renderer->Initialize();
	audio->Initialize();
	input->Initialize();

	renderer->CreateWindow("Viper Engine", 1280, 1024);


	//Create Audio System

	vector<viper::vec2> verts{
	{-4, 1 },
	{ 4, 1 },
	{-3, -4 },
	{0, 4 },
	{3, -4 },
	{-4, 1}
	};

	Font* font = new Font();
	font->Load("Farmshow.ttf", 80);

	Text* text = new Text(font);
	text->Create(*renderer, "Chihiro", viper::vec3{ 1,1,1 });



	shared_ptr<viper::Model> model = make_shared<viper::Model>(verts, viper::vec3{ 0, 0, 1 });

	//Create Actors
	vector <unique_ptr<viper::Actor>> actors;
	for (int i = 0; i < 10; i++) {
		viper::Transform transform{ viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024}, 0.0f, 10.0f };
		unique_ptr<Player> player = make_unique<Player>( transform, model);
		actors.push_back(move(player));
	}

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

		if (input->GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

		//Update Engine Systems
		input->Update();
		audio->Update();


		float speed = 200.0f;
		viper::vec2 direction{ 0, 0 };
		/*

		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) actor.GetTransform().rotation -= viper::math::degToRad(90 * time.GetDeltaTime());
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) actor.GetTransform().rotation += viper::math::degToRad(90 * time.GetDeltaTime());*/

		if (input->GetKeyDown(SDL_SCANCODE_W))direction.y = -1; // speed * time.GetDeltaTime();
		if (input->GetKeyDown(SDL_SCANCODE_S)) direction.y = 1; // speed * time.GetDeltaTime();
		if (input->GetKeyDown(SDL_SCANCODE_A)) direction.x = -1; // speed * time.GetDeltaTime();
		if (input->GetKeyDown(SDL_SCANCODE_D)) direction.x = 1; // speed * time.GetDeltaTime();

		if (direction.LengthSqr() > 0) {
		direction = direction.Normalized();
		for (auto& actor : actors) {
			actor->Draw(*renderer); // Draw the actor
		}
		}
		//Draw
		viper::vec3 color{ 0, 0, 0 };

		renderer->SetColor(color.r, color.g, color.b);			//Background color
		renderer->Clear();
		
		//model.Draw(renderer,input.GetMousePos(), 5.0f, 25.0f); // Draw the model at the center of the screen

		for(auto& actor : actors){
			actor->Draw(*renderer); // Draw the actor
		}

		text->Draw(*renderer, 40.0f, 40.0f);


		viper::vec2 speeds{ -140.0f, 0.0f };
		float length = speeds.Length();

		for (auto& star : stars) {
			star += speeds * time.GetDeltaTime();

			if (star[0] > 1280)  star[0] = 0;
			if (star[0] < 0)  star[0] = 1280;

			renderer->SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);
			renderer->DrawPoint(star.x, star.y);
		}

			renderer->Present(); // Render the screen
	}
	input->Shutdown();
	renderer->Shutdown();
	audio->Shutdown();
	return 0;
}

