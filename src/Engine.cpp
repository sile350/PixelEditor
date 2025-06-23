#include "Engine.h"

SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Event Engine::event;
bool Engine::running;
unsigned int Engine::SCREEN_WIDTH;
unsigned int Engine::SCREEN_HEIGHT;
TTF_Font* Engine::font_Geo40 = nullptr;
SDL_Cursor* Engine::cursorArrow = nullptr;
SDL_Cursor* Engine::cursorSizeWE = nullptr;
bool Engine::IsLeftMouseHeld = false;
int Engine::dxMouse;
bool Engine::isLeftMouseButtonHeld = false;

void Engine::Init(unsigned int width, unsigned int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

    running = true;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	UI::Init();

	window = SDL_CreateWindow(
		"SDL Drawing",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	font_Geo40 = TTF_OpenFont("fonts/Geo40.ttf", 40);

	cursorArrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	cursorSizeWE = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
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
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) 
		{
			SCREEN_WIDTH = event.window.data1;
			SCREEN_HEIGHT = event.window.data2;
		}
		if (event.type == SDL_MOUSEMOTION) {
			dxMouse = event.motion.xrel; // Сохраняем для других целей
			SDL_Point mousePos = { event.motion.x, event.motion.y };
			bool isOverSeparator = UI::IsPointInLine(mousePos);
			if (isLeftMouseButtonHeld && UI::isSeparatorDragging) {
				UI::SetSeparatorPosition(event.motion.x); // Перемещаем сепаратор к курсору
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			isLeftMouseButtonHeld = true;
			SDL_Point mousePos = { event.button.x, event.button.y };
			if (UI::IsPointInLine(mousePos)) {
				UI::isSeparatorDragging = true;
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
			isLeftMouseButtonHeld = false;
			UI::isSeparatorDragging = false;
		}
	}
}

void Engine::Render()
{
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

	//Draw UI
	UI::RenderUI();

    // Update screen
    SDL_RenderPresent(renderer);
}

void Engine::RenderText(const std::string& text, int x, int y, SDL_Color color, int fontSize, TTF_Font* font)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	int textWidth = textSurface->w;
	int textHeight = textSurface->h;

	SDL_FreeSurface(textSurface);

	SDL_Rect renderQuad = { x, y, textWidth, textHeight };

	SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

	SDL_DestroyTexture(textTexture);
}

void Engine::Cleanup()
{
	TTF_CloseFont(font_Geo40);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	if (cursorArrow) {
		SDL_FreeCursor(cursorArrow);
		cursorArrow = nullptr;
	}
	if (cursorSizeWE) {
		SDL_FreeCursor(cursorSizeWE);
		cursorSizeWE = nullptr;
	}

	TTF_Quit();
    SDL_Quit();
}

unsigned int Engine::GetScreenWidth()
{
    return SCREEN_WIDTH;
}

unsigned int Engine::GetScreenHeight()
{
    return SCREEN_HEIGHT;
}