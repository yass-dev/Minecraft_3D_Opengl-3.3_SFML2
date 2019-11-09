#ifndef MAP_H
#define MAP_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <stdlib.h>
#include <vector>

#include "Block.h"

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class Map
{
    public:
        Map();

        void draw(glm::mat4 *model_view, glm::mat4 *projection);
        void init_texture();
        void load();

        bool check_collision(glm::vec3 pos);

    private:
        std::vector<Block*> vecBlock;
        std::vector<float> vecVertex;
        std::vector<float> vecVertex_up;
        std::vector<float> vecTex_coord;

        std::vector<Texture> vecTexture;
        std::vector<GLuint> vecTextureID;

        Shader shader;
        Texture texture;
        Texture texture_up;

        GLuint shader_ID;
        GLuint texture_ID;
        GLuint texture_up_ID;

        GLuint vao;
        GLuint vbo;
};

#endif // MAP_H
