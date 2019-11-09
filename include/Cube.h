#ifndef CUBE_H
#define CUBE_H

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include <iostream>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "Shader.h"
#include "Texture.h"

class Cube
{
    public:
        Cube(float size_tmp, std::string vertex_shader, std::string fragment_shader);

        void draw(glm::mat4 *model_view, glm::mat4 *projection);
        void load();
        void set_position(glm::vec3 pos);

        glm::vec3 get_position() const;

    private:
        float size;
        float vertices[108];
        float color[108];
        float texture_coord[72];
        GLuint vbo;

        Shader shader;
        Shader shader_texture;
        Texture texture;

        glm::vec3 position;
};

#endif // CUBE_H
