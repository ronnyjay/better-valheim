#pragma once

#include "engine/shader_program.hpp"
#include <engine/texture.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <game/object.hpp>

#include <vector>

namespace game
{

class ellipses_object : public object
{
  public:
    ellipses_object();

    virtual void update(double dt) override;
    virtual void draw(const glm::mat4 &mvp) override;

  private:
    engine::vao m_vao;
    engine::vbo m_vbo;

    static constexpr uint16_t m_vertices = 36;
    std::vector<GLfloat> m_data;

    engine::shader_program m_shader_program;
    GLuint m_matrix_id;
};

}; // namespace game