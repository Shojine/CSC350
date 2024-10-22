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
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>




int main(int argc, char* argv[])
{
    SetBlendMode(BlendMode::Normal);

    Time time;
    Input input;

    //initalize
    Renderer* renderer = new Renderer;
    renderer->Initalize();
    renderer->CreateWindow("Game Engine", 800, 600);
    input.Initialize();


    Camera camera(800, 600);
    camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
    camera.SetProjection(90.0f, 800.0f / 600, 0.01f, 200.0f);
    Transform cameraTransform({ 0,0,-20 });

    Framebuffer framebuffer(*renderer, 800, 600);

    Transform transform{ {0,0,0}, glm::vec3{0,90,0},glm::vec3{2} };
    /*Image image;
    image.Load("Forest.jpg");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 85);*/



    std::shared_ptr<Model> model = std::make_shared<Model>();
    model->Load("teapot.obj");
    //model->SetColor({ 0, 255, 0, 255 });

    std::vector<std::unique_ptr<Actor>> actors;
    for (int i = 0; i < 5; i++)
    {
        Transform transform{ { randomf(-10.0f, 20.0f), randomf(-10.0f, 20.0f), randomf(-10.0f, 20.0f) }, glm::vec3{0, 0, 0}, glm::vec3{ randomf(2, 20) } };
        std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
        actor->SetColor({ (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256), 255 });
        actors.push_back(std::move(actor));
    }



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

        framebuffer.Clear(color_t{ 0,0,0,255 });


        int mx, my;
        SDL_GetMouseState(&mx, &my);



#pragma region AlphaBlend
        /* SetBlendMode(BlendMode::Normal);
         framebuffer.DrawImage(50, 100, image);
         SetBlendMode(BlendMode::Normal);
         framebuffer.DrawImage(mx, my, imageAlpha);*/
#pragma endregion



#pragma region PostProcess
         //PostProcess::Invert(framebuffer.m_buffer);
         //PostProcess::Monochrome(framebuffer.m_buffer);
         //PostProcess::Brightness(framebuffer.m_buffer, 90);
          //PostProcess::ColorBalance(framebuffer.m_buffer, 150, -50, -50);
          //PostProcess::Noise(framebuffer.m_buffer, 90);
          /*for (int i = 0; i < 4; i++)
          {
          PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
          }*/
          // PostProcess::GauseanBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

           //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
           //PostProcess::Monochrome(framebuffer.m_buffer);
           //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height, 40);
          //PostProcess::Threshold(framebuffer.m_buffer,100);
           //PostProcess::Posterize(framebuffer.m_buffer, 6);
           //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
#pragma endregion

        if (input.GetMouseButtonDown(2))
        {

            input.SetRelative(true);

            glm::vec3 direction{ 0 };
            if (input.GetKeyDown(SDL_SCANCODE_D))   direction.x = 1;
            if (input.GetKeyDown(SDL_SCANCODE_A))   direction.x = -1;
            if (input.GetKeyDown(SDL_SCANCODE_E))   direction.y = 1;
            if (input.GetKeyDown(SDL_SCANCODE_Q))   direction.y = -1;
            if (input.GetKeyDown(SDL_SCANCODE_W))   direction.z = 1;
            if (input.GetKeyDown(SDL_SCANCODE_S))   direction.z = -1;

            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.5f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.5f;

            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };

            cameraTransform.position += offset * 70.0f * time.GetDeltaTime();
        }
        else
        {
            input.SetRelative(false);
        }
        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

        //transform.position += direction * 70.0f * time.GetDeltaTime();
        //transform.rotation.z += 90* time.GetDeltaTime();
       // model->Draw(framebuffer, transform.GetMatrix(),camera);
        for (auto& actor : actors)
        {
            actor->Draw(framebuffer, camera);
        }


        framebuffer.Update();
        input.Update();
        //renderer = framebuffer;
        renderer->CopyFrameBuffer(framebuffer);

        // show screen
        renderer->RenderPresent();
    }

    return 0;
}
