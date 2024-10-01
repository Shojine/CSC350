#pragma once
#include <iostream>
#include <SDL.h>
class Renderer
{
public:
	bool Initalize();
	bool CreateWindow();
	void RenderClear();
	void RenderPresent();
	void SetRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);


public:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};