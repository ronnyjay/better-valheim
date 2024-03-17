#include "game/ellipses_object.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/shader.hpp>
#include <engine/shader_program.hpp>
#include <engine/texture.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>

#include <game/triangle_object.hpp>
#include <game/world.hpp>

#include <iostream>

int window_width = 1920;
int window_height = 1080;

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                            const char *message, const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification";
        break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // if (key == GLFW_KEY_W && action == GLFW_PRESS)
    //     w->forward = true;
    // if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    //     w->forward = false;
    // if (key == GLFW_KEY_S && action == GLFW_PRESS)
    //     w->backward = true;
    // if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    //     w->backward = false;
    // if (key == GLFW_KEY_A && action == GLFW_PRESS)
    //     w->left = true;
    // if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    //     w->left = false;
    // if (key == GLFW_KEY_D && action == GLFW_PRESS)
    //     w->right = true;
    // if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    //     w->right = false;
    // if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    //     w->up = true;
    // if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    //     w->up = false;
    // if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
    //     w->down = true;
    // if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
    //     w->down = false;

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        break;
    }
}

void window_size_callback(GLFWwindow *window, int w, int h)
{
    window_width = w;
    window_height = h;
    glViewport(0, 0, w, h);

    printf("%d, %d\n", w, h);
}

int main(int argc, char const *argv[])
{
    GLFWwindow *window;
    double current_time, last_time, dt;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        goto exit;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, "better-valheim", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        goto cleanup;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD." << std::endl;
        goto cleanup_window;
    }

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    glfwSwapInterval(1);

    stbi_set_flip_vertically_on_load(1);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    {
        game::world world_object;
        game::triangle_object triangle_object;
        game::ellipses_object ellipses_object;

        world_object.add_object(&ellipses_object);
        last_time = current_time = glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            current_time = glfwGetTime();
            dt = current_time - last_time;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            world_object.update(dt);
            world_object.draw();

            // Swap buffers and poll for IO events
            glfwSwapBuffers(window);
            glfwPollEvents();
            last_time = current_time;
        }
    }

cleanup_window:
    glfwDestroyWindow(window);
cleanup:
    glfwTerminate();
exit:

    return 0;
}
