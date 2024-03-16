#pragma once
#include <glm/glm.hpp>

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
    glm::vec3 m_player_pos;
    glm::vec3 m_player_dir;
    glm::vec3 m_player_up;

    glm::mat4 m_projection;
    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_mvp;
};
}; // namespace game
