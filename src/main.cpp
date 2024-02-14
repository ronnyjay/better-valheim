#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <engine/shader.hpp>
#include <engine/shader_program.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>

#include <iostream>
#include <stdexcept>

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

    window = glfwCreateWindow(640, 480, "better-valheim", NULL, NULL);
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

    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    {
        engine::shader_program shader_program;
        engine::vao triangle_vao;
        engine::vbo triangle_vbo;

        {
            engine::shader vertex_shader("resources/shaders/triangle.vs", GL_VERTEX_SHADER);
            engine::shader fragment_shader("resources/shaders/triangle.fs", GL_FRAGMENT_SHADER);

            shader_program.add_shader(vertex_shader.get_id());
            shader_program.add_shader(fragment_shader.get_id());
            shader_program.link();
        }

        // clang-format off
        static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
        };
        // clang-format on

        triangle_vbo.bind();
        triangle_vbo.init(g_vertex_buffer_data, sizeof(g_vertex_buffer_data), GL_STATIC_DRAW);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            shader_program.use();

            glEnableVertexAttribArray(0);

            triangle_vao.bind();
            triangle_vbo.bind();
            triangle_vao.set(0, 3, GL_FLOAT, 0, (void *)0);
            triangle_vao.draw(0, 3);
            triangle_vao.unbind();

            glDisableVertexAttribArray(0);

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
