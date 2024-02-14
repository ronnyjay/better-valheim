#ifndef VAO_HPP_
#define VAO_HPP_

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace engine
{

class vao
{
public:
  vao() { glGenVertexArrays(1, &m_id); }

  void bind() { glBindVertexArray(m_id); }

  void unbind() { glBindVertexArray(0); }

  void set(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, const void *pointer)
  {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
  }

  void setI(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, const void *pointer)
  {
    glEnableVertexAttribArray(index);
    glVertexAttribIPointer(index, size, type, stride, pointer);
  }

  void draw(int start, int count) { glDrawArrays(GL_TRIANGLES, start, count); }

  GLuint get_id() const { return m_id; }

  ~vao() { glDeleteVertexArrays(1, &m_id); }

private:
  GLuint m_id;
};

}; // namespace engine

#endif
