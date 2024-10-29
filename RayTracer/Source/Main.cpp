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
#include "Plane.h"
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>




int main(int argc, char* argv[])
{
    SetBlendMode(BlendMode::Normal);

    srand((unsigned int)time(NULL));
    Time time;
    
    //initalize
    Renderer renderer;
    renderer.Initalize();
    renderer.CreateWindow("RayTracer", 800, 600);

    Framebuffer framebuffer(renderer, renderer.m_width, renderer.m_width);

    Camera camera{ 70, (float)(renderer.m_width / renderer.m_height) };
    camera.SetView({ 0,0, -20 }, { 0,0,0 });
    
    std::vector<std::shared_ptr<Material>> colors;
    std::shared_ptr<Material> gray =   std::make_shared<Lambertian>(color3_t{ 0.5f });
    std::shared_ptr<Material> red =    std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> blue =   std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    //std::shared_ptr<Material> red = std::make_shared<Metal>(color3_t{ 1, 0, 0 }, 0.3f);
    //std::shared_ptr<Material> blue = std::make_shared<Metal>(color3_t{ 0, 0, 1 }, 0.1f);
    std::shared_ptr<Material> green =  std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
    std::shared_ptr<Material> yellow = std::make_shared<Lambertian>(color3_t{ 1, 1, 0 });
    std::shared_ptr<Material> purple = std::make_shared<Lambertian>(color3_t{ 1, 0, 1 });
    std::shared_ptr<Material> white =  std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
    colors.push_back(std::move(red));
    colors.push_back(std::move(blue));
    colors.push_back(std::move(yellow));
    colors.push_back(std::move(purple));
    colors.push_back(std::move(white));

    Scene scene;


    auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 1, 0 },gray); 
    scene.AddObject(std::move(plane));
    
    for (int i = 0; i < 5; i++)
    {
        auto object = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), 2.0f, colors[random(colors.size() - 1)]);
        scene.AddObject(std::move(object));
    }
   
    framebuffer.Clear(ColorConvert(color4_t{ 0,0.25f,0,1.0f}));
    scene.Render(framebuffer, camera, 5, 3);

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
        renderer.RenderClear();


        

        framebuffer.Update();
        
        //renderer = framebuffer;
        renderer.CopyFrameBuffer(framebuffer);

        // show screen
        renderer.RenderPresent();
      //  SDL_RenderPresent(renderer.m);
    }

    return 0;
}
