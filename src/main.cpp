#include <vector>
#include <fstream>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Shader.h"

void resize_callback(GLFWwindow* window, int width, int height);
void input(GLFWwindow* window);
std::string FileInString(std::ifstream&& file);

int w = 800, h = 600;
glm::mat4 proj;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(w, h, "OpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    proj = glm::perspective(glm::radians(60.0f), (float)w / (float)h, 0.1f, 100.0f);
    
    glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

    Shader sh;
    sh.AddShader(GL_VERTEX_SHADER, FileInString(std::ifstream("data/shader/standart_vert.glsl")).c_str(), "Standart vertex");
    sh.AddShader(GL_FRAGMENT_SHADER, FileInString(std::ifstream("data/shader/standart_frag.glsl")).c_str(), "Standart fragment");
    sh.Finish();

    Mesh m;
    m.CreateCube();

    glm::quat orientation = glm::quat(glm::vec3(0, 0, 0));
    glm::vec3 up = orientation * glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = orientation * glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -4.0f), glm::vec3(0.0f, 0.0f, -4.0f) + forward, up);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 0, 0));
    model = model * glm::mat4_cast(glm::quat(glm::vec3(0, glm::radians(60.0f), 0)));
    model = glm::scale(model, glm::vec3(1, 1, 1));

    while(!glfwWindowShouldClose(window))
    {
        input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sh.use();
        sh.setMat4("mvp", proj * view * model);
        m.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    w = width;
    h = height;
    if(!h) // Prevention zero-divide
        h = 1;

    proj = glm::perspective(glm::radians(60.0f), (float)w / (float)h, 0.1f, 100.0f);
}

std::string FileInString(std::ifstream&& file)
{
    if(!file.is_open())
        return std::string("");

    std::string src;
    getline(file, src, '\0');
    file.close();

    return src;
}
