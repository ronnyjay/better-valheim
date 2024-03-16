#pragma once

#include <glm/glm.hpp>

namespace game
{
class object
{
  public:
    virtual void draw(const glm::mat4 &mvp) = 0;
    virtual void update(double dt) = 0;
};
} // namespace game
