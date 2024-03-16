#include <game/world.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

using namespace game;

extern int window_width;
extern int window_height;

world::world() : m_player_pos(0, 0, 0), m_player_dir(0, 0, 1), m_player_up(0, 1, 0)
{
    m_projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 1000.0f);
    m_model = glm::mat4(1.0f);
    m_view = glm::lookAt(m_player_pos, m_player_pos + m_player_dir, m_player_up);

    m_mvp = m_projection * m_view * m_model;
}

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
        obj->draw(m_mvp);
    }
}
