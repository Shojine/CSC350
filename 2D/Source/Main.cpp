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
#include "Shader.h"
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
    camera.SetProjection(90.0f,800.0f / 600, 0.01f, 200.0f);
    Transform cameraTransform({ 0,0,-20 });

    Framebuffer framebuffer(*renderer, 800, 600);

    //Transform transform{ {0,0,0}, glm::vec3{0,90,0},glm::vec3{2} };
    /*Image image;
    image.Load("Forest.jpg");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 85);*/

    //shader 
    Shader::uniforms.view = camera.GetView();
    Shader::uniforms.projection = camera.GetProjection();
    Shader::uniforms.light.position = glm::vec3{ 10, 10, -10 };
    Shader::uniforms.light.direction = glm::vec3{ 0, 0, -1 }; // light pointing down
    Shader::uniforms.light.color = color3_t{ 1 };
    Shader::uniforms.ambient = color3_t{ 0.1f };
    
    Shader::framebuffer = &framebuffer;




    std::shared_ptr<Model> model = std::make_shared<Model>();
    model->Load("Models/cube.obj");
   // model->SetColor({ 0,1,1,1 });
   /* std::shared_ptr<Model> barel = std::make_shared<Model>();
    barel->Load("barel.obj");*/
   /* std::shared_ptr<Model> box = std::make_shared<Model>();
    box->Load("Models/box.obj");
    */
    //model->SetColor({ 0, 255, 0, 255 });



    std::vector<std::unique_ptr<Actor>> actors;
    /*Transform transform{ glm::vec3{ 0 }, glm::vec3{ 0 }, glm::vec3{ 2 } };
    std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
    actors.push_back(std::move(actor));*/
    //actors.push_back(std::move(actor1));
    //actors.push_back(std::move(actor2));


    std::shared_ptr<material_t> blue = std::make_shared<material_t>();
    blue->albedo = color3_t{ 0, 0, 1 };
    blue->specular = color3_t{ 1 };
    blue->shininess = 128.0f;

    std::shared_ptr<material_t> red = std::make_shared<material_t>();
    red->albedo = color3_t{ 1, 0, 0 };
    red->specular = color3_t{ 1 };
    red->shininess = 16.0f;



    {
        Transform transform{ glm::vec3{5,0,0},glm::vec3{0}, glm::vec3{5} };
        std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model, red);
        actors.push_back(std::move(actor));
    }

    {
        Transform transform{ glm::vec3{-5,0,0},glm::vec3{0}, glm::vec3{5} };
        std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model, blue);
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

        framebuffer.Clear(color_t{0,0,0,255});


        int mx, my;
        SDL_GetMouseState(&mx, &my);
        


#pragma region AlphaBlend
       /* SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(50, 100, image);
        SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(mx, my, imageAlpha);*/

        //framebuffer.DrawImage(50, 100,image);

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

            cameraTransform.position += offset * 20.0f * time.GetDeltaTime();
        }
        else
        {
            input.SetRelative(false);
        }
        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());
        Shader::uniforms.view = camera.GetView();

        //transform.position += direction * 70.0f * time.GetDeltaTime();
        //transform.rotation.z += 90* time.GetDeltaTime();
       // model->Draw(framebuffer, transform.GetMatrix(),camera);
        for (auto& actor : actors)
        {
            actor->GetTransform().rotation.y += time.GetDeltaTime() * 40;
            actor->Draw();
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
