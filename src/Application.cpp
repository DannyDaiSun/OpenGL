#include <iostream>
#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "ShaderProgram.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewInit();
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(LogError,NULL);

    
    float positions[] = {
        -0.5f,-0.5f,
        0.5f,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5f
    };
    VertexBuffer buffer(positions,sizeof(float)*2*4);

    VertexBufferLayout layout;
    layout.Push<GL_FLOAT>(2);

    VertexArray vertexArray;
    vertexArray.AddBuffer(buffer,layout);

    GLuint indices[] = {
        0,1,2,
        2,3,0
    };
    IndexBuffer indexBuffer(indices,6);


    ShaderProgram basicShader(R"(C:\Users\danny\source\repos\OpenGL\res\shaders\Basic.shader)");
    
    Renderer renderer;
    
    float r = 0.3495016f;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        

        r +=0.01f;
        r = r > 1.0f ? 0:r;

        basicShader.SetUniform4f("m_color", r, 0.9622642f, 0.9622642f, 1.0f);

        renderer.Draw(vertexArray, indexBuffer, basicShader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}