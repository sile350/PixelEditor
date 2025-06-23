#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Engine.h"
#include <iostream>

class UI
{
public:
	static SDL_Rect panelRect;
	static SDL_Rect headerRect;

	static SDL_Color separatorColor;
	static bool isSeparatorDragging;

	static void Init();
	static void RenderUI();
	static unsigned int GetSeparatorPosition();
	static bool IsPointInLine(const SDL_Point& point);
	static void SetSeparatorPosition(int x);

private:
	static unsigned int panelWidth;
	static unsigned int separatorPostion;
};

