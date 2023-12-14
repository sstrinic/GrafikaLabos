#include <iostream>
#include <string>

#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vendor\glm\gtc\type_ptr.hpp>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window("Vjezba4", SCR_WIDTH, SCR_HEIGHT);
  
    Model model("res/models/dragon.obj");
    Model model1("res/models/rectangle.obj");
    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/container.jpg");
    int width = 10;
    int height = 20;
    glm::mat4 view;


    Renderer render;
    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();

        glm::mat4 proj = glm::perspective(glm::radians(45.0f),(float)width / (float)height, 0.1f, 100.0f);
        
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));



        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 trans1 = glm::mat4(1.0f);

        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.41, 0.0, 1.0));
        trans1 = glm::rotate(trans1, (float)glfwGetTime()*2, glm::vec3(3.91, 0.0, 1.0));

        trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

        

        shader.Bind();
        shader.SetUniform4x4("model", trans);
        shader.SetUniform4x4("projection", proj);
        shader.SetUniform4x4("view", view);
        model.Draw(shader, tex);
        //shader.SetUniform4x4("model", trans1);
        //model1.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}