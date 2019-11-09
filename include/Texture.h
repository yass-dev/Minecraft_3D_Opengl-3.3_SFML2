#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>

class Texture
{
    public:
        Texture();
        Texture(std::string filename);
        Texture(const Texture &texture_copy);
        Texture& operator=(Texture const &textureACopier);
        virtual ~Texture();

        bool load();

        GLuint getID() const;

        void setFile(std::string filename);

    private:
        GLuint id;
        std::string file;
};

#endif // TEXTURE_H
