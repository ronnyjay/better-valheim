#pragma once

#include <game/object.hpp>

namespace game
{
class solid_object : public object
{
  public:
    solid_object();

    virtual void collide(solid_object *);

  private:
};
}; // namespace game