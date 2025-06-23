#include "UI.h"

SDL_Rect UI::panelRect;
SDL_Rect UI::headerRect;
unsigned int UI::panelWidth;
unsigned int UI::separatorPostion;
SDL_Color UI::separatorColor = { 83, 83, 83, 255 };
bool UI::isSeparatorDragging = false;

void UI::Init()
{
	panelRect = {0, 0, (int)(Engine::GetScreenWidth() * 0.2f), (int)Engine::GetScreenHeight()};
	headerRect = { 0, 0, (int)Engine::GetScreenWidth(),  (int)(Engine::GetScreenHeight() * 0.0625f) };
	separatorPostion = Engine::GetScreenWidth() * 0.2f;
}

void UI::RenderUI()
{
	//Draw panel rect
	SDL_SetRenderDrawColor(Engine::renderer, 53, 53, 53, 255);
	SDL_RenderFillRect(Engine::renderer, &UI::panelRect);

	//Draw header
	SDL_SetRenderDrawColor(Engine::renderer, 36, 36, 36, 255);
	SDL_RenderFillRect(Engine::renderer, &UI::headerRect);

	//Draw separator
	SDL_SetRenderDrawColor(Engine::renderer, separatorColor.r, separatorColor.g, separatorColor.b, separatorColor.a);
	SDL_RenderDrawLine(Engine::renderer, UI::GetSeparatorPosition(), 0, UI::GetSeparatorPosition(), Engine::GetScreenHeight());

	//Draw texts
	Engine::RenderText("Panel", 15, 3, {192,192,192,255}, 40, Engine::font_Geo40);
	Engine::RenderText("Holst", separatorPostion + 15, 3, {192,192,192,255}, 40, Engine::font_Geo40);
}

unsigned int UI::GetSeparatorPosition()
{
	return separatorPostion;
}

bool UI::IsPointInLine(const SDL_Point& point)
{
	bool isInLine = point.x > separatorPostion - 2 && point.x < separatorPostion + 2 && point.y >= 0 && point.y <= Engine::GetScreenHeight();
	if (isInLine || isSeparatorDragging) {
		SDL_SetCursor(Engine::cursorSizeWE);
		separatorColor = { 186, 186, 186, 255 };
	}
	else {
		SDL_SetCursor(Engine::cursorArrow);
		separatorColor = { 83, 83, 83, 255 };
	}
	return isInLine;
}

void UI::SetSeparatorPosition(int x)
{
	separatorPostion = SDL_clamp(x, 200, Engine::GetScreenWidth() * 0.4f); 
	panelRect.w = separatorPostion; 
}