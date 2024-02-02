#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

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

  try
  {
    if (!glfwInit())
      throw std::runtime_error("Failed to initialize GLFW.");

    window = glfwCreateWindow(640, 480, "better-valheim", NULL, NULL);
    if (!window)
      throw std::runtime_error("Failed to create GLFW window.");
  }
  catch (std::runtime_error &err)
  {
    std::cerr << err.what() << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD." << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f); // Alpha can only be 1
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers and poll for IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
