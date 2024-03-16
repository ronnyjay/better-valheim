#pragma once

#include <glad/gl.h>

namespace engine
{

class ebo
{
public:
  ebo() { glGenBuffers(1, &m_id); }

  ~ebo() { glDeleteBuffers(1, &m_id); }

  GLuint get_id() const { return m_id; }

  void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }

  void init(const void *data, unsigned int size, unsigned int usage)
  {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
  }

private:
  GLuint m_id;
};

}; // namespace engine
