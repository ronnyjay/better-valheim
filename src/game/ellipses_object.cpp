#include <game/ellipses_object.hpp>

#include <engine/shader.hpp>

using namespace game;

ellipses_object::ellipses_object()
{
    const float vertices = 36;

    const float major = 1.0f;
    const float minor = 0.25f;

    for (int i = 0; i <= vertices; i++)
    {
        float theta = 2.0f * M_PI * i / vertices;

        m_data.push_back(major * cosf(theta));
        m_data.push_back(minor * sinf(theta));
        m_data.push_back(10.0f);

        m_data.push_back(0.7f);
        m_data.push_back(0.2f);
        m_data.push_back(1.0f);
    }

    engine::shader vertex_shader("resources/shaders/debug.vs", GL_VERTEX_SHADER);
    engine::shader fragment_shader("resources/shaders/debug.fs", GL_FRAGMENT_SHADER);

    m_shader_program.add_shader(vertex_shader.get_id());
    m_shader_program.add_shader(fragment_shader.get_id());
    m_shader_program.link();

    m_vao.bind();
    m_vbo.bind();
    m_vao.set(0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    m_vao.set(1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    m_vbo.init(&m_data[0], (m_data.size() * sizeof(float)), GL_DYNAMIC_DRAW);
    m_vao.unbind();
    m_vbo.unbind();
}

void ellipses_object::update(double dt) {}

void ellipses_object::draw(const glm::mat4 &mvp)
{
    m_shader_program.bind();
    m_vbo.bind();
    m_vao.bind();

    m_matrix_id = glGetUniformLocation(m_shader_program.get_id(), "MVP");
    glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &mvp[0][0]);

    glDrawArrays(GL_TRIANGLE_FAN, 0, m_data.size() / 6);

    m_vao.unbind();
    m_vbo.unbind();
}