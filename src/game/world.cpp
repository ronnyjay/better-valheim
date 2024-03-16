#include <game/world.hpp>

using namespace game;

world::world() {}

void world::update(double dt)
{
    for (auto obj : m_objects)
    {
        obj->update(dt);
    }
}

void world::draw()
{
    for (auto obj : m_objects)
    {
        obj->draw();
    }
}
