#pragma once

#include <engine/shader.hpp>
#include <engine/shader_program.hpp>
#include <engine/texture.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>

#include <glm/glm.hpp>

namespace game
{

class object
{
  public:
    virtual void draw(const glm::mat4 &mvp) = 0;
    virtual void update(double dt) = 0;

  protected:
    engine::vao m_vao;
    engine::vbo m_vbo;

    engine::shader_program m_shader_program;

    GLuint m_matrix_id;

  private:
};

} // namespace game
