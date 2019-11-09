#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(std::string filename)
{
    file = filename;
}

Texture::Texture(const Texture &texture_copy)
{
    file = texture_copy.file;
    load();
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

bool Texture::load()
{
    sf::Image image;
    if (!image.loadFromFile(file))
    {
        std::cout << "Could not load : " << file << std::endl;
        return false;
    }

    if(glIsTexture(id) == GL_TRUE)
        glDeleteTextures(1, &id);

    image.flipHorizontally();
    image.flipVertically();

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setFile(std::string filename)
{
    file = filename;
}

GLuint Texture::getID() const
{
    return id;
}

Texture& Texture::operator=(Texture const &copy)
{
    file = copy.file;
    load();

    return *this;
}
