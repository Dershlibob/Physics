#include <GL/glew.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Engine/Camera.h"
#include "Engine/Shader.h"
#include "Engine/Window.h"
#include "Engine/Model.h"
#include "Engine/Shapes.h"
#include "Engine/Scene.h"
#include "Engine/ModelManager.h"

#include "SceneManager.h"
#include "Background.h"
#include "PlayerCharacter.h"
#include "Enemy.h"

using namespace std;

static float random(float min, float max)
{
    return (min + static_cast <float> (rand()) / 
        (static_cast <float> (RAND_MAX / (max - min))));
}

float Entity::dt = 0;

int main()
{
    Window* window = Window::getInstance();

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    window->HideMouse(true);
    glfwSwapInterval(0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    srand(time(0));

    glm::vec3 ModelPos(3.0f, 0.0f, 0.0f);
    glm::vec3 LightPosition = { 0.0f, 2.0f, 10.0f };
    glm::vec3 LightColour = { 1.0f, 1.0f, 1.0f };

    Camera cam;
    
    ModelManager::LoadModel("src/Models/Monkey/monkey.fbx");
    ModelManager::LoadModel("src/Models/cube/cube.fbx");
    ModelManager::LoadModel("src/Models/Sphere/sphere.fbx");

    Shader bgShader("src/Shader/Instancing.shader");
    Shader BasicShader("src/Shader/Basic.shader");
    Shader LightingShader("src/Shader/Lighting.shader");
    Shader ModelShader("src/Shader/Model.shader");
    
    Scene::Init(&LightingShader, &cam);

    shared_ptr<Entity> sceneManager = Scene::Instantiate(SceneManager());
    shared_ptr<Entity> player = Scene::Instantiate(PlayerCharacter());
                       player->SetModel(ModelManager::getModel("monkey"));
           

    Background bg(&cam, &bgShader, 10000);

    vector<Shape> Shapes;

    LightingShader.Bind();
    LightingShader.setVec3("objectColour", glm::vec3(1.0f, 0.5f, 0.31f));
    LightingShader.setVec3("lightColour", LightColour);
    LightingShader.setVec3("lightPosition", LightPosition);

    BasicShader.Bind();
    BasicShader.setVec3("u_Colour", LightColour);
    
    Shape Light(shapes::CUBE, &BasicShader, &cam);
          Light.SetPosition(LightPosition);
          Light.scale = glm::vec3(0.2f, 0.2f, 0.2f);

    glEnable(GL_DEPTH_TEST);

    double deltaTime = 0.0;
    double prevTime = 0.0;
    double currentTime = 0.0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        // main start func
        Scene::StartEntity();

        currentTime = glfwGetTime();
        deltaTime = currentTime - prevTime;
        prevTime = currentTime;

        Entity::dt = deltaTime;

        //cam.ProcessInput(window->getWindow(), deltaTime);
        cam.UpdateCamera();

        // main update func
        Scene::UpdateEntities(deltaTime);

        LightingShader.setVec3("viewPos", cam.cameraPos);

        if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwTerminate();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BasicShader.Bind();
        BasicShader.setVec3("u_Colour", LightColour);
        Light.Draw(deltaTime);
        bg.Draw();

        // main render func
        Scene::DrawEntities();
        
        // Clean up objects marked to be deleted.
        Scene::FinalDestroy();

        /* Swap front and back buffers */
        glfwSwapBuffers(window->getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}