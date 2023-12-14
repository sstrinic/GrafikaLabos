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
  
    Model model("res/models/bird.obj");
    Model model1("res/models/teapot.obj");
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

        glm::mat4 proj = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        
        view = glm::lookAt(glm::vec3(0.0f, 8.0f, 4.5f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 trans1 = glm::mat4(1.0f);

        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.41, 0.0, 1.0));
        trans1 = glm::rotate(trans1, (float)glfwGetTime()*5, glm::vec3(5.31, 0.0, 1.0));
        trans1 = glm::scale(trans1, glm::vec3(0.25f, 0.25f, 0.25f));
        trans = glm::translate(trans, glm::vec3(2.0f, 1.0f, 1.0f));

        shader.Bind();
        shader.SetUniform4x4("model", trans);
        shader.SetUniform4x4("projection", proj);
        shader.SetUniform4x4("view", view);
        model.Draw(shader, tex);
        shader.SetUniform4x4("model", trans1);
        model1.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}