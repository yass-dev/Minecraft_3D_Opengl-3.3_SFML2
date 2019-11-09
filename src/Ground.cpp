#include "Ground.h"

Ground::Ground(float size_tmp, std::string vertex_shader, std::string fragment_shader)
    : shader(vertex_shader, fragment_shader), size(20.0f)
{
    size = size_tmp;

    texture.setFile("Textures/photorealistic_ground/ground025.jpg");
    if (!texture.load())
    {
        std::cout << "Error : Ground texture doesn't loaded" << std::endl;
    }

    shader.charger();

    float vertices_tmp[18] =
    {
        -size, 0, -size,
        size, 0, -size,
        size, 0, size,

        -size, 0, -size,
        -size, 0, size,
        size, 0, size
    };

    float texture_coord_tmp[12] =
    {
        0, 0,   size, 0,   size, size,
        0, 0,   0, size,   size, size
    };

    for (unsigned int i = 0; i < 18; i++)
    {
        vertices[i] = vertices_tmp[i];
    }
    for (unsigned int i = 0; i < 12; i++)
    {
        texture_coord[i] = texture_coord_tmp[i];
    }
}

void Ground::draw(glm::mat4 *model_view, glm::mat4 *projection)
{
    glUseProgram(shader.getProgramID());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texture_coord);

    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(*projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(*model_view));

    glBindTexture(GL_TEXTURE_2D, texture.getID());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}
