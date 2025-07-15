#include "Core/Random.h"
#include "Core/Time.h"
#include "Math\Vector2.h"
#include "Math\Math.h"
#include "Renderer\Renderer.h"
#include "Input/InputSystem.h"

//#include <fmod.h>
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

	//Create Audio Systems

	//Initialize objects


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




		if (input.GetMouseButtonPressed(viper::is::MouseButton::Left)) {
			points.push_back(input.GetMousePos());
		}


		if (input.GetMouseButtonDown(viper::is::MouseButton::Left)) {
			viper::vec2 position = input.GetMousePos();

			if (points.empty()) {
				points.push_back(position);
			}
			else if ((position - points.back()).Length() > 10)
			{
				points.push_back(position);
			}
		}



		//Update Engine Systems
		input.Update();

		//Get Input
		////if (input.GetKeyPressed(SDL_SCANCODE_A)) {
		//	cout << "Pressed." << endl;
		//}

		//if (input.GetMouseButtonDown(viper::is::MouseButton::Left)) {
		//	cout << "Mouse Pressed." << endl;
		//}
		//viper::vec2 mouse = input.GetMousePos();
		//cout << "(" << mouse.x << ", " << mouse.y << ")" << endl;



		//Draw
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
			renderer.Present(); // Render the screen
		}

		for (int i = 0; i < (int)points.size() - 1; i++) {
			// set color or random color
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}



		for (int i = 0; i < (int)points.size() - 1; i++) {
			// set color or random color
			renderer.SetColor(viper::random::getRandomInt(255), viper::random::getRandomInt(255), viper::random::getRandomInt(255), viper::random::getRandomInt(255));
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		/*       Code for Disco Lights
*
for (auto& lights : disco) {


			  renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);

			  renderer.DrawLine(viper::random::getRandomInt(1280), viper::random::getRandomInt(1024), viper::random::getRandomInt(1280), viper::random::getRandomInt(1024));

}
	 */

	}
}

