#include "engine/shader.hpp"
#include <game/triangle_object.hpp>

using namespace game;

// clang-format off
const GLfloat triangle_object::m_data[][6] = {
    { -1.0f, -1.0f, 10.0f, 0.0f, 0.0f, 0.0f, },
    { +1.0f, -1.0f, 10.0f, 0.7f, 0.2f, 1.0f, },
    { +1.0f, +1.0f, 10.0f, 0.0f, 0.0f, 0.0f, },
    { -1.0f, -1.0f, 10.0f, 0.0f, 0.0f, 0.0f, },
    { +1.0f, +1.0f, 10.0f, 0.0f, 0.0f, 0.0f, },
    { -1.0f, +1.0f, 10.0f, 0.7f, 0.2f, 1.0f, },
};
// clang-format on

triangle_object::triangle_object()
{
    engine::shader vertex_shader("resources/shaders/debug.vs", GL_VERTEX_SHADER);
    engine::shader fragment_shader("resources/shaders/debug.fs", GL_FRAGMENT_SHADER);

    m_shader_program.add_shader(vertex_shader.get_id());
    m_shader_program.add_shader(fragment_shader.get_id());
    m_shader_program.link();

    m_vao.bind();
    m_vbo.bind();
    m_vao.set(0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    m_vao.set(1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * (sizeof(float))));
    m_vbo.init(m_data, sizeof(m_data), GL_DYNAMIC_DRAW);
    m_vao.unbind();
    m_vbo.unbind();
}

void triangle_object::update(double dt) {}

void triangle_object::draw(const glm::mat4 &mvp)
{
    m_shader_program.bind();
    m_vbo.bind();
    m_vao.bind();

    m_matrix_id = glGetUniformLocation(m_shader_program.get_id(), "MVP");
    glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &mvp[0][0]);

    m_vao.draw(0, 6);

    m_vao.unbind();
    m_vbo.unbind();
}
