#pragma once

#include <SDL.h>
#include "UI.h"
#include <iostream>
#include <string>

class Engine
{
public:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_Event event;

	static TTF_Font* font_Geo40;

	static SDL_Cursor* cursorArrow;
	static SDL_Cursor* cursorSizeWE;

	static bool WindowIsRunning();
	static void PollEvent();
	static void Render();
	static void RenderText(const std::string& text, int x, int y, SDL_Color color, int fontSize, TTF_Font* font);
	static void Init(unsigned int width, unsigned int height);
	static void Cleanup();
	static bool IsLeftMouseHeld;

	static unsigned int GetScreenWidth();
	static unsigned int GetScreenHeight();

	static bool isLeftMouseButtonHeld; // Переименовано
	static bool IsLeftMouseButtonHeld() { return isLeftMouseButtonHeld; } // Геттер

	static int dxMouse;

private:
	static unsigned int SCREEN_WIDTH;
	static unsigned int SCREEN_HEIGHT;

	static bool running;
	
	Engine() {}
};