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
#include "Engine/UI.h"
#include "Engine/Texture.h"

#include "SceneManager.h"
#include "Background.h"
#include "PlayerCharacter.h"
#include "Enemies/Enemy.h"
#include "Minimap.h"

using namespace std;

static float random(float min, float max)
{
    return (min + static_cast <float> (rand()) / 
        (static_cast <float> (RAND_MAX / (max - min))));
}

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
    
    glEnable(GL_DEPTH_TEST);

    srand(time(0));

    glm::vec3 ModelPos(3.0f, 0.0f, 0.0f);
    glm::vec3 LightPosition = { 0.0f, 20.0f, 200.0f };
    glm::vec3 LightColour = { 1.0f, 1.0f, 1.0f };

    Camera cam;
    
    ModelManager::LoadModel("Models/Monkey/monkey.fbx");
    ModelManager::LoadModel("Models/cube/cube.fbx");
    ModelManager::LoadModel("Models/Sphere/sphere.fbx");

    Shader bgShader("src/Shader/Instancing.shader");
    //Shader BasicShader("src/Shader/Basic.shader");
    Shader LightingShader("src/Shader/Lighting.shader");
    Shader ModelShader("src/Shader/Model.shader");
    Shader UIShader("src/Shader/UI.shader");

    Texture MapTexture("map.png");
    Texture EnemyTexture("enemy.png");
    
    Scene::Init(&LightingShader, &cam);

    shared_ptr<Entity> sceneManager = Scene::Instantiate(SceneManager());
    shared_ptr<Entity> player = Scene::Instantiate(PlayerCharacter());
                       player->SetModel(ModelManager::GetModel("monkey"));

    Background bg(&cam, &bgShader, 10000);

    LightingShader.Bind();
    LightingShader.setVec3("objectColour", glm::vec3(1.0f, 0.5f, 0.31f));
    LightingShader.setVec3("lightColour", LightColour);
    LightingShader.setVec3("lightPosition", LightPosition);

    //BasicShader.Bind();
    //BasicShader.setVec3("u_Colour", LightColour);

    double deltaTime = 0.0;
    double prevTime = 0.0;
    double currentTime = 0.0;

    Minimap map(&UIShader, &MapTexture, 200, 200, glm::vec3(WIN_WIDTH - 150, 150, 0.0f));
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwTerminate();

        currentTime = glfwGetTime();
        deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        Entity::dt = deltaTime;

        Scene::FinalDestroy();// Clean up objects marked to be deleted.
        Scene::StartEntity();// main start func
        Scene::UpdateEntities(deltaTime);// main update func

        cam.UpdateCamera();
        LightingShader.Bind();
        LightingShader.setVec3("viewPos", cam.cameraPos);

        map.Update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        bg.Draw();

        Scene::DrawEntities();// main render func

        glDisable(GL_CULL_FACE);
        map.SS_to_NDC();
        map.DrawUI();
        glEnable(GL_CULL_FACE);

        /* Swap front and back buffers */
        glfwSwapBuffers(window->getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}