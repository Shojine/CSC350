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
#include "Triangle.h"
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>


void InitSceneCornelBox(Scene& scene, Camera& camera)
{
    scene.SetSky(color3_t{ .02 },color3_t{0.5});
    camera.SetFOV(20.0f);
    camera.SetView({ 0,-0.6f,-20 }, { 0,0,0 });

    auto ground_material = std::make_shared<Lambertian>(color3_t(1.0f));

    std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });

    auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0,-2,0}, glm::vec3{0,0,0}}, ground_material);

    auto plane2 = std::make_unique<Plane>(Transform{ glm::vec3{-1.5f,2,0}, glm::vec3{0,0,-90}}, red);
    scene.AddObject(std::move(plane2));

    auto plane3 = std::make_unique<Plane>(Transform{ glm::vec3{1.5f,2,0}, glm::vec3{0,0,-90} }, green);
    scene.AddObject(std::move(plane3));

    auto plane4 = std::make_unique<Plane>(Transform{ glm::vec3{0,0,-5}, glm::vec3{0,90,90} }, ground_material);
    scene.AddObject(std::move(plane4));

    auto plane5 = std::make_unique<Plane>(Transform{ glm::vec3{0,0.65f,0}, glm::vec3{0,0,0} }, ground_material);
    scene.AddObject(std::move(plane5)); 

    auto cubeLight = std::make_unique<Model>(Transform{ glm::vec3{0,0.6,-13}, glm::vec3{0,0,0 }, glm::vec3{0.7f,0.05f,0.3f} }, std::make_shared<Emissive>(color3_t{1}, 20.0f));
    cubeLight->Load("Models/cube.obj");


    auto cube1 = std::make_unique<Model>(Transform{ glm::vec3{0.8,-1.5f,-9}, glm::vec3{0,30,0 }, glm::vec3{0.6f,1.5,0.6f} },ground_material);
    cube1->Load("Models/cube.obj");
    scene.AddObject(std::move(cube1));

    auto object = std::make_unique<Sphere>(Transform{ glm::vec3{-0.5,-1.5f,-9} }, 0.5f, std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f));
    scene.AddObject(std::move(object));


    scene.AddObject(std::move(cubeLight));
    scene.AddObject(std::move(plane));
}


void InitScene01(Scene& scene, Camera& camera)
{
    camera.SetFOV(20.0f);
    camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

    auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f));
    scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0,-2,0 } }, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomf();
            glm::vec3 center(a + 0.9 * randomf(), 0.2, b + 0.9 * randomf());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
                    auto fuzz = randomf(0.0f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 1, 0 } }, 1.0f, material1));

    auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ -4, 1, 0 } }, 1.0f, material2));

    auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 4, 1, 0 } }, 1.0f, material3));
}



void initScene(Scene& scene)
{
    scene.SetSky(HSVtoRGB(240, 1, 0.01),HSVtoRGB(250,5,0.001));
    std::vector<std::shared_ptr<Material>> colors;
    std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
    std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0, 1, 1 });
    std::shared_ptr<Material> redMet = std::make_shared<Metal>(color3_t{ 1, 0, 0 }, 0.6f);
    std::shared_ptr<Material> blueMet = std::make_shared<Metal>(color3_t{ 0, 0, 1 }, 0.1f);
    std::shared_ptr<Material> yellowMet = std::make_shared<Metal>(color3_t{ 1, 1, 0 }, 0.3f);
    std::shared_ptr<Material> greenMet = std::make_shared<Metal>(color3_t{ 0, 1, 0 }, 0.6f);
    std::shared_ptr<Material> OrangeEmiss = std::make_shared<Emissive>(color3_t{ 1, 0.5f, 0.25f }, 20.4f);
    std::shared_ptr<Material> WhiteEmiss = std::make_shared<Emissive>(color3_t{ 1, 1, 1}, 10.0f);
    std::shared_ptr<Material> BlueEmiss = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 1.3f);
    std::shared_ptr<Material> whiteDia = std::make_shared<Dielectric>(color3_t{ 1, 1, 1 }, 1.3f);
    std::shared_ptr<Material> blueDia = std::make_shared<Dielectric>(color3_t{ 0, 1, 1 }, 2.0f);
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
    std::shared_ptr<Material> yellow = std::make_shared<Lambertian>(color3_t{ 1, 1, 0 });
    std::shared_ptr<Material> purple = std::make_shared<Lambertian>(color3_t{ 1, 0, 1 });
    std::shared_ptr<Material> white = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
    colors.push_back(std::move(red));
    colors.push_back(std::move(blue));
    colors.push_back(std::move(yellow));
    colors.push_back(std::move(purple));
    colors.push_back(std::move(white));
    colors.push_back(std::move(blueMet));
    colors.push_back(std::move(yellowMet));
    colors.push_back(std::move(greenMet));
    colors.push_back(std::move(OrangeEmiss));
    colors.push_back(std::move(whiteDia));
    colors.push_back(std::move(blueDia));
    //colors.push_back(std::move(WhiteEmiss));



    auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0,-1.5,0}, glm::vec3{0,0,0} }, gray);
    scene.AddObject(std::move(plane));

    auto barel = std::make_unique<Model>(Transform{ glm::vec3{0,1.5,4}, glm::vec3{0,0,40 }, glm::vec3{4} }, std::make_shared<Emissive>(HSVtoRGB(180, 0.9, 0.5),10.0f));
    barel->Load("Models/cube.obj");
    scene.AddObject(std::move(barel));

    for (int i = 0; i < 10; i++)
    {
    auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{0}, glm::vec3{10})} }, 2.0f, colors[random(colors.size())]);
    scene.AddObject(std::move(object));
    }


   // auto triangle = std::make_unique<Triangle>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 0, 2, 0 }, glm::vec3{ 2, 0, 0 }, green); scene.AddObject(std::move(triangle));

    //for (int i = 0; i < 10; i++)
    //{
    //    /*auto object = std::make_unique<Sphere>(random(glm::vec3{ 0 }, glm::vec3{ 13 }), 2.0f, colors[random(colors.size())]);
    //    scene.AddObject(std::move(object));*/

    //    auto triangle = std::make_unique<Triangle>(random(glm::vec3{ 0 }, glm::vec3{ 5 }), random(glm::vec3{ 5 }, glm::vec3{ 10 }), random(glm::vec3{ 0 }, glm::vec3{ 5 }), colors[random(colors.size())]);
    //    scene.AddObject(std::move(triangle));
    //}
}


int main(int argc, char* argv[])
{
    SetBlendMode(BlendMode::Normal);

    srand((unsigned int)time(NULL));
    Time time;
    
    //initalize
    Renderer renderer;
    renderer.Initalize();
    renderer.CreateWindow("RayTracer", 800, 600);

    Framebuffer framebuffer(renderer, renderer.m_width, renderer.m_height);

    Camera camera{ 70, (float)(renderer.m_width / (float)renderer.m_height) };
    //camera.SetView({ 1,5, -10 }, { 0,0,30 });
    Scene scene;
    
    //initScene(scene);
    InitScene01(scene,camera);
    //InitSceneCornelBox(scene, camera);
    scene.Update();
   
    framebuffer.Clear(ColorConvert(color4_t{ 0,0.25f,0,1.0f}));
    scene.Render(framebuffer, camera, 1,6);


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
