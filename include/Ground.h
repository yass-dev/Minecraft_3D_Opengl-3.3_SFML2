#ifndef GROUND_H
#define GROUND_H

#include <iostream>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "Shader.h"
#include "Texture.h"

class Ground
{
    public:
        Ground(float size_tmp, std::string vertex_shader, std::string fragment_shader);

        void draw(glm::mat4 *model_view, glm::mat4 *projection);

    private:
        Shader shader;
        Texture texture;

        float size;
        float vertices[18];
        float texture_coord[12];
};

#endif // GROUND_H
