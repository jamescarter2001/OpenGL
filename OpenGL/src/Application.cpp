#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtx/string_cast.hpp"

void printMatrix(glm::mat4x4& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Disable compatibility mode.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    unsigned int windowX = 1280;
    unsigned int windowY = 720;

    float aspectRatio = (float) windowX / (float) windowY;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Sandbox", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "[GLEW] Initialization Error!" << std::endl;
    }

    std::cout << "[OpenGL] " << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glDebugMessageCallback(DebugCallback, 0);

    float vertex[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
    };

    float vertex3D[] = {
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.8f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.8f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.2f, 0.6f, 0.8f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.8f, 0.0f, 0.8f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.2f, 0.6f, 0.8f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.8f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.8f, 1.0f,
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int indices3D[] = {
        0, 1, 2,
        1, 3, 4,
        5, 6, 3,
        7, 3, 6,
        2, 4, 7,
        0, 7, 6,
        0, 5, 1,
        1, 5, 3,
        5, 0, 6,
        7, 4, 3,
        2, 1, 4,
        0, 2, 7
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();

    std::unique_ptr<VertexArray> vao = std::make_unique<VertexArray>();
    vao->Bind();

    //std::unique_ptr<VertexBuffer> vertexBuffer = std::make_unique<VertexBuffer>(vertex, sizeof(vertex));
    //std::unique_ptr<IndexBuffer> indexBuffer = std::make_unique<IndexBuffer>(indicies, sizeof(indicies));

    std::unique_ptr<VertexBuffer> vertexBuffer = std::make_unique<VertexBuffer>(vertex3D, sizeof(vertex3D));
    std::unique_ptr<IndexBuffer> indexBuffer = std::make_unique<IndexBuffer>(indices3D, sizeof(indices3D));

    std::unique_ptr<VertexBufferLayout> layout = std::make_unique<VertexBufferLayout>();

    // Layout define
    layout->Push<float>(3); // X, Y, Z
    layout->Push<float>(4); // Color
    vao->AddBuffer(*vertexBuffer, *layout);

    float fieldOfView = 90.0f;
    float d = 1 / glm::tan(glm::radians(fieldOfView / 2));

    // Map Z values of vertices in a chosen nearZ and farZ range into -1 -> 1 space, with anything outside being automatically clipped by GPU.
    float nearZ = 1.0f;
    float farZ = 10.0f;
    float Zrange = nearZ - farZ;

    float A = (-farZ - nearZ) / Zrange;
    float B = 2.0f * farZ * nearZ / Zrange;

    // Unused orthographic projection.
    //glm::mat4 ortho = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    // glm uses column major ordering, requiring matrices to be entered row down and column across.
    glm::mat4 proj = glm::mat4((d / aspectRatio), 0.0f, 0.0f, 0.0f,
                               0.0f, d, 0.0f, 0.0f,
                               0.0f, 0.0f, A, 1.0f,
                               0.0f, 0.0f, B, 0.0f);

    glm::vec4 test = glm::vec4(0.5f, 0.5f, 0.8f, 1.0f);

    glm::mat4 t_rotate = glm::mat4(1.0f);
    t_rotate = glm::rotate(t_rotate, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 translation = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 1.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 1.0f, 0.0f,
                                      0.0f, 0.0f, 2.0f, 1.0f);

    glm::vec4 result = proj * translation * test;
    std::cout << glm::to_string(result);
    //glm::mat4 finalMatrix = proj * translation;

    std::string shaderPath("res/shaders/Basic3D.shader");
    std::unique_ptr<Shader> shaderProgram = std::make_unique<Shader>(shaderPath);

    /*std::string texturePath("res/textures/dummy.png");
    std::unique_ptr<Texture> texture = std::make_unique<Texture>(texturePath);

    shaderProgram->SetUniform1i("u_Texture", 0);*/
    shaderProgram->SetUniformMat4f("u_Projection", proj);
    shaderProgram->SetUniformMat4f("u_Translation", translation);


    vao->Unbind();
    vertexBuffer->Unbind();
    indexBuffer->Unbind();
    shaderProgram->Unbind();

    float r = 0.0f;
    float inc = -0.5f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        renderer->Clear();

        if (r >= 360.0f || r <= -360.0f) {
            std::cout << "[Renderer] Resetting r value" << std::endl;
            r = 0.0f;
        }
        r += inc;

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
        shaderProgram->SetUniformMat4f("u_Rotation", trans);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //shaderProgram->SetUniform4f(std::string("u_Color"), r, 0.3f, 0.8f, 1.0f);
        renderer->Draw(*vao, *indexBuffer, *shaderProgram);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}