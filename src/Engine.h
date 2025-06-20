#pragma once

#include <SDL.h>
#include <iostream>

class Engine
{
public:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_Event event;

	static bool WindowIsRunning();
	static void PollEvent();
	static void Render();
	static void Init(unsigned int width, unsigned int height);
	static void Cleanup();

private:
	static unsigned int SCREEN_WIDTH;
	static unsigned int SCREEN_HEIGHT;

	static bool running;
	
	Engine() {}
};