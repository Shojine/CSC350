#include "Renderer.h"
#include <iostream>
#include <SDL.h>



int main(int argc, char* argv[])
{

    Renderer* renderer = new Renderer;
    renderer->Initalize();
    renderer->CreateWindow();

   
    while (true)
    {
        // clear screen
        renderer->SetRenderColor(0, 0, 0, 0);
        renderer->RenderClear();

        // show screen
        renderer->RenderPresent();
    }

    return 0;
}