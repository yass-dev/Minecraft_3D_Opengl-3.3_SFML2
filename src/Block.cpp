#include "Block.h"

Block::Block(glm::vec3 pos, GLuint shaderID)
    :   position(pos), block_size(BLOCK_SIZE), vertices_size(0),
        vbo(0), vao(0), is_visible(true)
{

    shader_ID = shaderID;

    float cube[] =
    {
        position.x, position.y, position.z,
        position.x + block_size, position.y, position.z,
        position.x + block_size, position.y + block_size, position.z,     // Face 1
        position.x, position.y, position.z,
        position.x, position.y + block_size, position.z,
        position.x + block_size, position.y + block_size, position.z,     // Face 1

        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z,
        position.x + block_size, position.y + block_size, position.z,       // Face 2
        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z,         // Face 2

        position.x, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z,      // Face 3
        position.x, position.y, position.z + block_size,
        position.x, position.y, position.z,
        position.x + block_size, position.y, position.z,    // Face 3

        position.x, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,        // Face 4
        position.x, position.y, position.z + block_size,
        position.x, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,        // Face 4

        position.x, position.y, position.z,
        position.x, position.y, position.z + block_size,
        position.x, position.y + block_size, position.z + block_size,     // Face 5
        position.x, position.y, position.z,
        position.x, position.y + block_size, position.z,
        position.x, position.y + block_size, position.z + block_size,     // Face 5

        position.x, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z,         // Face 6
        position.x, position.y + block_size, position.z + block_size,
        position.x, position.y + block_size, position.z,
        position.x + block_size, position.y + block_size, position.z
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
        0, 0,   0, 1,   1, 1     // Face 6
    };

    for(unsigned int i = 0; i < 108; i++)
    {
        vertices[i] = cube[i];
    }

    for(unsigned int i = 0; i < 72; i++)
    {
        texture_coord[i] = texture_coord_tmp[i];
    }

    this->load();
}

Block::~Block()
{
    delete[] vertices;
    delete[] texture_coord;
}

void Block::load()
{
    int tex_coord_size = sizeof(texture_coord);
    vertices_size = sizeof(vertices);

    if (glIsBuffer(vbo) == GL_TRUE)
        glDeleteBuffers(1, &vbo);
    if (glIsVertexArray(vao) == GL_TRUE)
        glDeleteVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices_size + tex_coord_size, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, vertices);
        glBufferSubData(GL_ARRAY_BUFFER, vertices_size, tex_coord_size, texture_coord);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices_size));
            glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}


void Block::set_position(float x, float y, float z)
{
    set_position(glm::vec3(x, y, z));
}

void Block::set_position(glm::vec3 pos)
{
    position = pos;

    block_size /= 2;

    float cube[] =
    {
        position.x, position.y, position.z,
        position.x + block_size, position.y, position.z,
        position.x + block_size, position.y + block_size, position.z,     // Face 1
        position.x, position.y, position.z,
        position.x, position.y + block_size, position.z,
        position.x + block_size, position.y + block_size, position.z,     // Face 1

        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z,
        position.x + block_size, position.y + block_size, position.z,       // Face 2
        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z,         // Face 2

        position.x, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z,      // Face 3
        position.x, position.y, position.z + block_size,
        position.x, position.y, position.z,
        position.x + block_size, position.y, position.z,    // Face 3

        position.x, position.y, position.z + block_size,
        position.x + block_size, position.y, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,        // Face 4
        position.x, position.y, position.z + block_size,
        position.x, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,        // Face 4

        position.x, position.y, position.z,
        position.x, position.y, position.z + block_size,
        position.x, position.y + block_size, position.z + block_size,     // Face 5
        position.x, position.y, position.z,
        position.x, position.y + block_size, position.z,
        position.x, position.y + block_size, position.z + block_size,     // Face 5

        position.x, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z + block_size,
        position.x + block_size, position.y + block_size, position.z,         // Face 6
        position.x, position.y + block_size, position.z + block_size,
        position.x, position.y + block_size, position.z,
        position.x + block_size, position.y + block_size, position.z
    };

    for(unsigned int i = 0; i < 108; i++)
    {
        vertices[i] = cube[i];
    }

    this->load();
}

glm::vec3 Block::get_position() const
{
    return position;
}

float Block::get_block_size() const
{
    return BLOCK_SIZE;
}

void Block::set_texture_ID(GLuint texture_ID_tmp, GLuint texture_up_ID_tmp)
{
    texture_ID = texture_ID_tmp;
    texture_up_ID = texture_up_ID_tmp;
}

float *Block::get_vertices()
{
    return vertices;
}

float *Block::get_tex_coord()
{
    return texture_coord;
}

int Block::get_vertices_size() const
{
    return sizeof(vertices) / sizeof(float);
}

int Block::get_tex_coord_size() const
{
    return sizeof(texture_coord) / sizeof(float);
}

void Block::set_visibility(bool on)
{
    is_visible = on;
}
