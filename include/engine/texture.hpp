#pragma once

#include <glad/gl.h>

#include <stb_image/stb_image.h>

#include <stdexcept>
#include <string>

namespace engine
{

class texture
{
  public:
    texture(const std::basic_string<char> imagePath)
    {
        unsigned char *data = stbi_load(imagePath.c_str(), &m_width, &m_height, &m_channels, 0);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (data)
        {
            glGenTextures(1, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            throw std::runtime_error("Failed to load texture: " + imagePath);
        }

        stbi_image_free(data);
    }

    void bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    GLuint get_id() const { return m_id; }

    ~texture() {}

  private:
    GLuint m_id;
    int m_width;
    int m_height;
    int m_channels;
};

}; // namespace engine
