#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

	bool Initalize();
	bool CreateWindow(std::string name, int width, int height);
	void RenderClear();
	void RenderPresent();
	void SetRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void CopyFrameBuffer(const class Framebuffer& buffer);

	//void operator = (const class Framebuffer& buffer);
	void operator = (const class Framebuffer& buffer);
	friend class Framebuffer;

	int m_width;
	int m_height;


private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;


};