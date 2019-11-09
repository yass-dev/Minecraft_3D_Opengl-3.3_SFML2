#include "SkyBox.h"

SkyBox::SkyBox(float size_tmp, std::string vertex_shader, std::string fragment_shader)
    : shader(vertex_shader, fragment_shader), is_animated(false), angle(0.0f)
{
    shader.charger();
    size = size_tmp;

    float cube[] =
    {
        0.0, 0.0, 0.0,
        size, 0.0, 0.0,
        0.0, size, 0.0,

        size, size, 0.0,
        size, 0.0, 0.0,
        0.0, size, 0.0,


        0.0, size, size,
        0.0, 0.0, size,
        0.0, size, 0.0,

        0.0, 0.0, 0.0,
        0.0, 0.0, size,
        0.0, size, 0.0,


        size, size, size,
        size, 0.0, size,
        size, size, 0.0,

        size, 0.0, 0.0,
        size, 0.0, size,
        size, size, 0.0,


        0.0, 0.0, size,
        size, 0.0, size,
        0.0, size, size,

        size, size, size,
        size, 0.0, size,
        0.0, size, size,
    };

    float color_tmp[] =
    {
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,

        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,

        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,

        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
    };

    for(unsigned int i = 0; i < 108; i++)
    {
        vertices[i] = cube[i];
        color[i] = color_tmp[i];
    }
}

void SkyBox::draw(glm::mat4 *model_view, glm::mat4 *projection)
{
    glUseProgram(shader.getProgramID());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, color);

    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(*projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(*model_view));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}
