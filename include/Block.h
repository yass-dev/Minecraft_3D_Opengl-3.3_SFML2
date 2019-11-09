#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>

#include "Shader.h"
#include "Texture.h"

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#define BLOCK_SIZE 2

class Block
{
    public:
        Block(glm::vec3 pos, GLuint shaderID);
        virtual ~Block();

        void load();
        void set_position(glm::vec3 pos);
        void set_position(float x, float y, float z);
        void set_texture_ID(GLuint texture_ID_tmp, GLuint texture_up_ID_tmp);
        void set_visibility(bool on);

        glm::vec3 get_position() const;

        float get_block_size() const;
        float *get_vertices();
        float *get_tex_coord();

        int get_vertices_size() const;
        int get_tex_coord_size() const;

    private:
        float vertices[108];
        float texture_coord[72];
        int vertices_size;
        GLuint vbo;
        GLuint vao;

        GLuint shader_ID;

        GLuint texture_ID;
        GLuint texture_up_ID;

        glm::vec3 position;
        float block_size;
        float is_visible;
};

#endif // BLOCK_H
