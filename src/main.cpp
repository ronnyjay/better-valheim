#include "engine/texture.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#define GLM_ENABLE_EXPERIMENTAL

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <engine/shader.hpp>
#include <engine/shader_program.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>

#include <iostream>
#include <stdexcept>

constexpr int width = 1920;
constexpr int height = 1080;

void error_callback(int error, const char *description) { throw std::runtime_error(description); }

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char const *argv[])
{
    GLFWwindow *window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        goto exit;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "better-valheim", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        goto cleanup;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD." << std::endl;
        goto cleanup_window;
    }

    glfwSwapInterval(1);

    stbi_set_flip_vertically_on_load(1);

    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    {
        engine::shader_program shader_program;
        engine::vao triangle_vao;
        engine::vbo triangle_vbo;
        engine::texture triangle_texture("resources/textures/beans.bmp");

        {
            engine::shader vertex_shader("resources/shaders/triangle.vs", GL_VERTEX_SHADER);
            engine::shader fragment_shader("resources/shaders/triangle.fs", GL_FRAGMENT_SHADER);

            shader_program.add_shader(vertex_shader.get_id());
            shader_program.add_shader(fragment_shader.get_id());
            shader_program.link();
        }

        // clang-format off
        static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        };
        // clang-format on

        glm::mat4 Projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.0f, 100.0f); // In world coordinates
        glm::mat4 Model = glm::mat4(1.0f);

        triangle_vbo.bind();
        triangle_vbo.init(g_vertex_buffer_data, sizeof(g_vertex_buffer_data), GL_STATIC_DRAW);

        GLuint matrix_id = glGetUniformLocation(shader_program.get_id(), "MVP");
        GLuint texture_id = glGetUniformLocation(shader_program.get_id(), "tex");

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            shader_program.use();

            glm::vec3 eye(sin(glfwGetTime()), cos(glfwGetTime()), 1);
            glm::vec3 center(eye.x, eye.y, 0);
            glm::vec3 up(0, 1, 0);

            glm::mat4 view = glm::lookAt(eye, center, up);
            glm::mat4 mvp = Projection * view * Model;

            glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);

            glActiveTexture(GL_TEXTURE0);
            triangle_texture.bind();
            glUniform1i(texture_id, 0);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            triangle_vbo.bind();
            triangle_vao.bind();
            triangle_vao.set(0, 3, GL_FLOAT, 5*sizeof(float), (void *)(0*sizeof(float)));

            triangle_vao.set(1, 2, GL_FLOAT, 5*sizeof(float), (void *)(3*sizeof(float)));
            triangle_vao.draw(0, 6);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

            triangle_vao.unbind();

            // Swap buffers and poll for IO events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

cleanup_window:
    glfwDestroyWindow(window);
cleanup:
    glfwTerminate();
exit:

    return 0;
}
