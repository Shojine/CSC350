#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"
#include <iostream>
#include <SDL.h>




int main(int argc, char* argv[])
{

    Renderer* renderer = new Renderer;
    renderer->Initalize();
    renderer->CreateWindow("Game Engine", 800, 600);
    Framebuffer framebuffer(*renderer, 800, 600);

    Image image;
    image.Load("Forest.jpg");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 300);

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

        //for (int i = 0; i < 10; i++)
        //{
        //    int x = rand() % framebuffer.m_width;
        //    int y = rand() % framebuffer.m_height;
        //    int x2 = rand() % framebuffer.m_width + 100;
        //    int y2 = rand() % framebuffer.m_height + 100;
        //    
        //    
        //    
        //    
        //  //  framebuffer.DrawTriangle(100, 100, 200, 200, 300, 300, color_t{ 255,255,255 });
        //    framebuffer.DrawPoint(x, y, color_t{ 255,255,255 });
        //}

        int mx, my;
        SDL_GetMouseState(&mx, &my);

        SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(50, 100, image);
        SetBlendMode(BlendMode::Alpha);
        framebuffer.DrawImage(mx, my, imageAlpha);
        
        
        /*int x, y;
        CubicPoint(300, 400, 300, 100, mx, my, 600, 400, t, x, y);

        framebuffer.DrawRect(x - 20 , y - 20, 40, 40, color_t{255,255,255,255});*/
  
#pragma region PostProcess
       //PostProcess::Invert(framebuffer.m_buffer);
       //PostProcess::Monochrome(framebuffer.m_buffer);
       //PostProcess::Brightness(framebuffer.m_buffer, 90);
        //PostProcess::ColorBalance(framebuffer.m_buffer, 150, -50, -50);
        //PostProcess::Noise(framebuffer.m_buffer, 90);
        /*for (int i = 0; i < 10; i++)
        {
        PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        }*/
        //PostProcess::GauseanBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height, 10);
       //PostProcess::Threshold(framebuffer.m_buffer,100);
        //PostProcess::Posterize(framebuffer.m_buffer, 6);
#pragma endregion

        
        framebuffer.Update();
        //renderer = framebuffer;
        renderer->CopyFrameBuffer(framebuffer);


        // show screen
        renderer->RenderPresent();
    }

    return 0;
}