#include "Map.h"

Map::Map()
    :   shader("Shaders/texture.vert", "Shaders/texture.frag"), texture("Textures/Minecraft/diamond_block.png"),
        texture_up("Textures/Minecraft/diamond_block.png")
{
    shader.charger();
    texture.load();
    texture_up.load();

    shader_ID = shader.getProgramID();
    texture_ID = texture.getID();
    texture_up_ID = texture_up.getID();

    float block_size = BLOCK_SIZE;
    for (float x = -50.0f; x <= 50.f; x += block_size        * 1)
    {
        for (float z = -50.0f; z <= 50.f; z += block_size    * 1)
        {
            if (x < -49 || z < -49 || x > 49 || z > 49)
            {
                for (float y = 0.0f; y < 20; y += block_size)
                {
                    vecBlock.push_back(new Block(glm::vec3(x, y, z), shader.getProgramID()));
                    vecBlock.back()->set_texture_ID(texture.getID(), texture_up.getID());
                }
            }
            else
            {
                vecBlock.push_back(new Block(glm::vec3(x, 0.0f, z), shader.getProgramID()));        // GROUND
                vecBlock.back()->set_texture_ID(texture.getID(), texture_up.getID());
            }
        }
    }
    load();
}

void Map::init_texture()
{

}

void Map::load()
{
    for (unsigned int i = 0; i < vecBlock.size(); i++)
    {
        float *vertex = vecBlock[i]->get_vertices();
        float *tex_coords = vecBlock[i]->get_tex_coord();
        int vertex_size = vecBlock[i]->get_vertices_size();
        int tex_size = vecBlock[i]->get_tex_coord_size();
        int j = 0;
        for (; j < vertex_size - 18; j++)
        {
            vecVertex.push_back(vertex[j]);
        }
        for (; j < vertex_size; j++)
        {
            vecVertex_up.push_back(vertex[j]);
        }
        for (j = 0; j < tex_size; j++)
        {
            vecTex_coord.push_back(tex_coords[j]);
        }
        delete vertex;
        delete tex_coords;
    }

    int vertices_size = (vecVertex.size() + vecVertex_up.size()) * sizeof(float);
    int tex_coord_size = vecTex_coord.size() * sizeof(float);

    if (glIsBuffer(vbo) == GL_TRUE)
        glDeleteBuffers(1, &vbo);
    if (glIsVertexArray(vao) == GL_TRUE)
        glDeleteVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices_size + tex_coord_size, 0, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vecVertex.size() * sizeof(float), &vecVertex[0]);
        glBufferSubData(GL_ARRAY_BUFFER, vecVertex.size() * sizeof(float), vecVertex_up.size() * sizeof(float), &vecVertex_up[0]);
        glBufferSubData(GL_ARRAY_BUFFER, vertices_size, tex_coord_size, &vecTex_coord[0]);
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

void Map::draw(glm::mat4 *model_view, glm::mat4 *projection)
{
    glUseProgram(shader_ID);

        glBindVertexArray(vao);
            glUniformMatrix4fv(glGetUniformLocation(shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(*projection));
            glUniformMatrix4fv(glGetUniformLocation(shader_ID, "modelview"), 1, GL_FALSE, glm::value_ptr(*model_view));

            glBindTexture(GL_TEXTURE_2D, texture_ID);
               glDrawArrays(GL_TRIANGLES, 0, vecVertex.size() / 3);
            glBindTexture(GL_TEXTURE_2D, 0);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
                for (unsigned int i = 0; i < vecVertex.size(); i ++)
                {
                    //vecVertex[i] = 0;
                }
                glBufferSubData(GL_ARRAY_BUFFER, 0, vecVertex.size() * sizeof(float), &vecVertex[0]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindTexture(GL_TEXTURE_2D, texture_up_ID);
                glDrawArrays(GL_TRIANGLES, vecVertex.size() / 3, vecVertex_up.size() / 3);
            glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);
    glUseProgram(0);
}

bool Map::check_collision(glm::vec3 pos)
{
    for (unsigned int i = 0; i < vecBlock.size(); i++)
    {
        glm::vec3 box = vecBlock[i]->get_position();
        if (pos.x >= box.x
            && pos.x < box.x + vecBlock[i]->get_block_size()
            && pos.y >= box.y
            && pos.y < box.y + vecBlock[i]->get_block_size()
            && pos.z >= box.z
            && pos.z < box.z + vecBlock[i]->get_block_size())
               return true;
    }
    return false;
}
