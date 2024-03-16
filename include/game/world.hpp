#pragma once

#include <game/object.hpp>
#include <list>

namespace game
{

class world
{
  public:
    world();

    void update(double dt);
    void draw();
    void add_object(object *const obj) { m_objects.push_back(obj); }

  private:
    std::list<object *> m_objects;
};
}; // namespace game
