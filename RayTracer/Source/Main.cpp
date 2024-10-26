#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h"
#include "Actor.h"
#include "Random.h"
#include "Tracer.h"
#include "Scene.h"
#include "Material.h"
#include "SceneObject.h"
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>




int main(int argc, char* argv[])
{
    SetBlendMode(BlendMode::Normal);

    Time time;
    

    //initalize
    Renderer* renderer = new Renderer;
    renderer->Initalize();
    renderer->CreateWindow("RayTracer", 800, 600);
   
    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(*renderer, renderer->m_width, renderer->m_width);

    Camera camera{ 70, (float)(renderer->m_width / renderer->m_height) };
    camera.SetView({ 0,0,-20 }, { 0,0,0 });

    Scene scene;

    std::shared_ptr<Material> material = std::make_shared<Material>(color3_t{ 1,0,0 });
    auto object = std::make_unique<Sphere>(glm::vec3{ 0 }, 2.0f, material);

    scene.AddObject(std::move(object));
    


   
    bool quit = false;
    while (!quit)
    {
        time.Tick();
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
        

        framebuffer.Clear(ColorConvert(color4_t{ 0.7f,0.8f,0.7f,1}));

        scene.Render(framebuffer, camera);

        

        framebuffer.Update();
        
        //renderer = framebuffer;
        renderer->CopyFrameBuffer(framebuffer);

        // show screen
        renderer->RenderPresent();
      //  SDL_RenderPresent(renderer.m);
    }

    return 0;
}
