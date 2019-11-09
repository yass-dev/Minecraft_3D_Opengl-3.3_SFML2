#ifndef OBJLOADER_H
#define OBJLOADER_H

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
#include <fstream>
#include <string>
#include <stdio.h>

#include "Shader.h"

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class OBJLoader
{
    public:
        OBJLoader();

        void load(const char *filename);
        void draw(glm::mat4 *model_view, glm::mat4 *projection);
        void set_color(glm::vec3 color_tmp);
        void set_position(glm::vec3 position);

    private:
        std::vector<std::string> split(std::string s, std::string delimiter);
        int atoi(std::string number);

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> uvs;
        std::vector<glm::vec3> colors;
        std::vector<float> vecVertices;

        glm::vec3 color;
        glm::vec3 position;

        int vertices_number;

        Shader shader;

        GLuint vbo;
        GLuint vao;
};
#endif
