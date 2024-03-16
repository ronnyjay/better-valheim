#pragma once

#include <engine/texture.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <game/object.hpp>

namespace game
{

class triangle_object : public object
{
  public:
    triangle_object();

    virtual void update(double dt) override;
    virtual void draw() override;

  private:
    engine::vao m_vao;
    engine::vbo m_vbo;

    static GLfloat m_vertices[];
    // engine::texture m_texture;
};
}; // namespace game
