#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include <iostream>
#include <SDL.h>




int main(int argc, char* argv[])
{

    Renderer* renderer = new Renderer;
    renderer->Initalize();
    renderer->CreateWindow("Game Engine", 800, 600);
    Framebuffer framebuffer(*renderer, 800, 600);
    Image image;
    image.Load("Halloween.png");

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
            
            
            
            
          //  framebuffer.DrawTriangle(100, 100, 200, 200, 300, 300, color_t{ 255,255,255 });
            framebuffer.DrawPoint(x, y, color_t{ 255,255,255 });
       framebuffer.DrawImage(x, y, image);
        }

        
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        /*int ticks = SDL_GetTicks() * 0.001f;
        float t = std::abs(std::sin(ticks));
        int x, y;
        CubicPoint(300, 400, 300, 100, mx, my, 600, 400, t, x, y);
        framebuffer.DrawRect(x - 20 , y - 20, 40, 40, color_t{255,255,255,255})*/;
        


        framebuffer.DrawTriangle(50, 100, 100, 150, 200, 50, color_t{ 255,255,255,255 });
        int xc = 50, xy = 50, r = 40;
        framebuffer.DrawLine(50, 40, 20, 15, color_t{255,255,255 });
       //framebuffer.DrawRect(10, 10, 100, 100, color_t{ 255,255,255,255 });
       framebuffer.DrawCircle(xc, xy, r, color_t{ 255,255,255,255 });
       framebuffer.DrawLinearCurve(100, 100, 200, 200, color_t{ 230,20,200,255 });
       /*framebuffer.DrawQuadraticCurve(100, 200, 200, 100, mx , my, color_t{ 230,20,200,255 });
       framebuffer.DrawCubicCurve(100, 200,100, 100, mx, my, x, y, color_t{ 230,20,200,255 });*/
       framebuffer.Update();
        //renderer = framebuffer;
        renderer->CopyFrameBuffer(framebuffer);


        // show screen
        renderer->RenderPresent();
    }

    return 0;
}