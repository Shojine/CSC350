#include "Renderer.h"
#include "Framebuffer.h"
#include <iostream>
#include <SDL.h>



int main(int argc, char* argv[])
{

    Renderer* renderer = new Renderer;
    renderer->Initalize();
    renderer->CreateWindow("Game Engine", 800, 600);
    Framebuffer framebuffer(*renderer, 200, 150);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
      

        // clear screen
        renderer->RenderClear();

        framebuffer.Clear(color_t{0,0,0,255});

        for (int i = 0; i < 10; i++)
        {
            int x = rand() % framebuffer.m_width;
            int y = rand() % framebuffer.m_height;
            int x2 = rand() % framebuffer.m_width;
            int y2 = rand() % framebuffer.m_height;
            
            
            
            //framebuffer.DrawLine(x, y, x2, y2, color_t{255,255,255 });
          //  framebuffer.DrawTriangle(100, 100, 200, 200, 300, 300, color_t{ 255,255,255 });
            framebuffer.DrawPoint(x, y, color_t{ 255,255,255 });
        }
       // framebuffer.DrawTriangle(100, 100, 200, 200, 100, 100, color_t{ 255,255,255 });

       framebuffer.DrawRect(10, 10, 100, 100, color_t{ 255,255,255,255 });

        framebuffer.Update();
        //renderer = framebuffer;
        renderer->CopyFrameBuffer(framebuffer);


        // show screen
        renderer->RenderPresent();
    }

    return 0;
}