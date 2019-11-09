#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "Shader.h"

class SkyBox
{
    public:
        SkyBox(float size_tmp, std::string vertex_shader, std::string fragment_shader);
        void draw(glm::mat4 *model_view, glm::mat4 *projection);

    private:
        float size;
        float angle;
        float vertices[108];
        float color[108];

        bool is_animated;

        Shader shader;
};

#endif // SKYBOX_H
