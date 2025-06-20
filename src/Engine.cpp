#include "Engine.h"

SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Event Engine::event;
bool Engine::running;
unsigned int Engine::SCREEN_WIDTH;
unsigned int Engine::SCREEN_HEIGHT;

void Engine::Init(unsigned int width, unsigned int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

    running = true;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
		"SDL Drawing",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

bool Engine::WindowIsRunning()
{
	return running;
}

void Engine::PollEvent()
{
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) running = false;
	}
}

void Engine::Render()
{
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Рисование точки (белая)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, 100, 100);

    // Рисование линии (красная)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 50, 50, 150, 150);

    // Рисование прямоугольника (зеленый контур)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect rect = { 200, 200, 100, 100 };
    SDL_RenderDrawRect(renderer, &rect);

    // Рисование заполненного прямоугольника (синий)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect filledRect = { 350, 350, 100, 100 };
    SDL_RenderFillRect(renderer, &filledRect);

    // Update screen
    SDL_RenderPresent(renderer);
}

void Engine::Cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}