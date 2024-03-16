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

int width = 1920;
int height = 1080;

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
    width = w;
    height = h;
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    {
        engine::shader_program shader_program;
        engine::vao triangle_vao;
        engine::vbo triangle_vbo;
        engine::texture triangle_texture("resources/textures/grass.jpg");

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

        game::world world_object;
        game::triangle_object triangle_object;

        world_object.add_object(&triangle_object);
        last_time = current_time = glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            current_time = glfwGetTime();
            dt = current_time - last_time;

            world_object.update(dt);
            world_object.draw();

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
            triangle_vao.set(0, 3, GL_FLOAT, 5 * sizeof(float), (void *)(0 * sizeof(float)));

            triangle_vao.set(1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));
            triangle_vao.draw(0, 6);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

            triangle_vao.unbind();

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
