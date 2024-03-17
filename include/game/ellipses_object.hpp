#pragma once

#include <game/object.hpp>

#include <vector>

namespace game
{

class ellipses_object : public object
{
  public:
    ellipses_object();

    virtual void draw(const glm::mat4 &mvp) override;
    virtual void update(double dt) override;

  private:
    std::vector<GLfloat> m_data;
};

}; // namespace game