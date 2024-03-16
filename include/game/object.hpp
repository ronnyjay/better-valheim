#pragma once

namespace game
{
class object
{
  public:
    virtual void draw() = 0;
    virtual void update(double dt) = 0;
};
} // namespace game
