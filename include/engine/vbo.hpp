#ifndef VBO_HPP_
#define VBO_HPP_

#include <glad/gl.h>

namespace engine
{

class vbo
{

public:
  vbo() { glGenBuffers(1, &m_id); }

  void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

  void init(const void *data, unsigned int size, unsigned int usage)
  {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
  }

  GLuint get_id() const { return m_id; }

  ~vbo() { glDeleteBuffers(1, &m_id); }

private:
  GLuint m_id;
};

}; // namespace engine

#endif