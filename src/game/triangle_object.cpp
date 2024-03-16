#include <game/triangle_object.hpp>

using namespace game;

// clang-format off
GLfloat m_vertices[] = {
    -1.0f, -1.0f, 100, 200, 233
    +1.0f, -1.0f, 100, 200, 233
    -1.0f, +1.0f, 100, 200, 233
};
// clang-format on

triangle_object::triangle_object()
{
    m_vao.bind();
    m_vbo.bind();
    m_vao.set(0, 2, GL_FLOAT, 5 * sizeof(float), (void *)0);
    m_vao.set(1, 3, GL_FLOAT, 5 * sizeof(float), (void *)(2 * (sizeof(float))));
    m_vao.unbind();
    m_vbo.unbind();
}

void triangle_object::update(double dt) {}

void triangle_object::draw() {}
