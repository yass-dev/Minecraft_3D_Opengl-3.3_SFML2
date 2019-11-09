#include "Cube.h"

Cube::Cube(float size_tmp, std::string vertex_shader, std::string fragment_shader)
    :   shader(vertex_shader, fragment_shader), texture("Textures/photorealistic_objets/object005.jpg"),
        shader_texture("Shaders/texture.vert", "Shaders/texture.frag"), position(glm::vec3(0, 0, 0))
{
    shader.charger();
    shader_texture.charger();

    size = size_tmp;

    if (!texture.load())
    {
        std::cout << "Error : Cube texture doesn't loaded" << std::endl;
    }

    float cube[] =
    {
        position.x + -size, position.y + -size, position.z + -size,
        position.x + size, position.y + -size, position.z + -size,
        position.x + size, position.y + size, position.z + -size,     // Face 1
        position.x + -size, position.y + -size, position.z + -size,
        position.x + -size, position.y + size, position.z + -size,
        position.x + size, position.y + size, position.z + -size,     // Face 1

        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + -size,
        position.x + size, position.y + size, position.z + -size,       // Face 2
        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + -size,         // Face 2

        position.x + -size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + -size,      // Face 3
        position.x + -size, position.y + -size, position.z + size,
        position.x + -size, position.y + -size, position.z + -size,
        position.x + size, position.y + -size, position.z + -size,    // Face 3

        position.x + -size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + size, position.z + size,        // Face 4
        position.x + -size, position.y + -size, position.z + size,
        position.x + -size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + size,        // Face 4

        position.x + -size, position.y + -size, position.z + -size,
        position.x + -size, position.y + -size, position.z + size,
        position.x + -size, position.y + size, position.z + size,     // Face 5
        position.x + -size, position.y + -size, position.z + -size,
        position.x + -size, position.y + size, position.z + -size,
        position.x + -size, position.y + size, position.z + size,     // Face 5

        position.x + -size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + -size,         // Face 6
        position.x + -size, position.y + size, position.z + size,
        position.x + -size, position.y + size, position.z + -size,
        position.x + size, position.y + size, position.z + -size
    };



    float texture_coord_tmp[] =
    {
        0, 0,   1, 0,   1, 1,     // Face 1
        0, 0,   0, 1,   1, 1,     // Face 1

        0, 0,   1, 0,   1, 1,     // Face 2
        0, 0,   0, 1,   1, 1,     // Face 2

        0, 0,   1, 0,   1, 1,     // Face 3
        0, 0,   0, 1,   1, 1,     // Face 3

        0, 0,   1, 0,   1, 1,     // Face 4
        0, 0,   0, 1,   1, 1,     // Face 4

        0, 0,   1, 0,   1, 1,     // Face 5
        0, 0,   0, 1,   1, 1,     // Face 5

        0, 0,   1, 0,   1, 1,     // Face 6
        0, 0,   0, 1,   1, 1
    };

    for(unsigned int i = 0; i < 108; i++)
    {
        vertices[i] = cube[i];
    }

    for(unsigned int i = 0; i < 72; i++)
    {
        texture_coord[i] = texture_coord_tmp[i];
    }
}

void Cube::load()
{
    int vertices_size = 108 * sizeof(float);

    if (glIsBuffer(vbo) == GL_TRUE)
        glDeleteBuffers(1, &vbo);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::draw(glm::mat4 *model_view, glm::mat4 *projection)
{
    glUseProgram(shader_texture.getProgramID());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texture_coord);

    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(*projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(*model_view));

    glBindTexture(GL_TEXTURE_2D, texture.getID());

        glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}

void Cube::set_position(glm::vec3 pos)
{
    position = pos;

    float cube[] =
    {
        position.x + -size, position.y + -size, position.z + -size,
        position.x + size, position.y + -size, position.z + -size,
        position.x + size, position.y + size, position.z + -size,     // Face 1
        position.x + -size, position.y + -size, position.z + -size,
        position.x + -size, position.y + size, position.z + -size,
        position.x + size, position.y + size, position.z + -size,     // Face 1

        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + -size,
        position.x + size, position.y + size, position.z + -size,       // Face 2
        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + -size,         // Face 2

        position.x + -size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + -size,      // Face 3
        position.x + -size, position.y + -size, position.z + size,
        position.x + -size, position.y + -size, position.z + -size,
        position.x + size, position.y + -size, position.z + -size,    // Face 3

        position.x + -size, position.y + -size, position.z + size,
        position.x + size, position.y + -size, position.z + size,
        position.x + size, position.y + size, position.z + size,        // Face 4
        position.x + -size, position.y + -size, position.z + size,
        position.x + -size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + size,        // Face 4

        position.x + -size, position.y + -size, position.z + -size,
        position.x + -size, position.y + -size, position.z + size,
        position.x + -size, position.y + size, position.z + size,     // Face 5
        position.x + -size, position.y + -size, position.z + -size,
        position.x + -size, position.y + size, position.z + -size,
        position.x + -size, position.y + size, position.z + size,     // Face 5

        position.x + -size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + size,
        position.x + size, position.y + size, position.z + -size,         // Face 6
        position.x + -size, position.y + size, position.z + size,
        position.x + -size, position.y + size, position.z + -size,
        position.x + size, position.y + size, position.z + -size
    };

    for(unsigned int i = 0; i < 108; i++)
    {
        vertices[i] = cube[i];
    }

    load();
}

glm::vec3 Cube::get_position() const
{
    return position;
}
