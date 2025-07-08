#pragma once
#include <SDL3/SDL.h>
#include <iostream>
using namespace std;
namespace viper {
	class Renderer
	{
	public:
		Renderer() {}
		bool Initialize();
		void Shutdown();
		bool CreateWindow(const string& name, int width, int height);

		void Clear();
		void Present();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x, float y);

	private:
		SDL_Window* _window{ nullptr };
		SDL_Renderer* _renderer{ nullptr };
	};
};