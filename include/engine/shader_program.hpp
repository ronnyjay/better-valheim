#ifndef SHADER_PROGRAM_HPP_
#define SHADER_PROGRAM_HPP_

#include <glad/gl.h>
#include <stdexcept>
#include <string>

namespace engine
{

class shader_program
{
public:
  shader_program() { m_id = glCreateProgram(); }

  void add_shader(GLuint shader_id) { glAttachShader(m_id, shader_id); }
  void use()
  {
    glUseProgram(m_id);
  }

  void link()
  {
    GLint result = GL_FALSE;
    GLint logLength;
    std::string programLinkError;

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength)
    {
      programLinkError.resize(logLength);
      glGetProgramInfoLog(m_id, logLength, NULL, &programLinkError[0]);
    }

    if (result != GL_TRUE)
    {
      std::string error = "Error compiling shader: ";
      error += programLinkError;

      throw std::runtime_error(error + programLinkError);
    }
  }

  GLuint get_id() { return m_id; }

private:
  GLuint m_id;
};

}; // namespace engine

#endif
