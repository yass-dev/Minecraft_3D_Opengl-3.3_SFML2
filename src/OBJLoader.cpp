#include "OBJLoader.h"

OBJLoader::OBJLoader()
    : shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag"), position(0, 0, 0)
{
    shader.charger();
}

void OBJLoader::load(const char *filename)
{
    std::string line;
    std::ifstream file(filename, std::ios::in);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices, temp_normals;

    if (file)
    {
        std::cout << "3D file : " << filename << " opened !" << std::endl;
        while (std::getline(file, line))
        {
            std::vector<std::string> split_line = split(line, " ");

            if (line[0] == 'v')
            {
                if (line[1] == ' ')
                {
                    glm::vec3 a;
                    a.x = position.x + std::stof(split_line[1]);
                    a.y = position.y + std::stof(split_line[2]);
                    a.z = position.z + std::stof(split_line[3]);
                    temp_vertices.push_back(a);
                }
                else if (line[1] == 'n')
                {
                    glm::vec3 a;
                    a.x = position.x + std::stof(split_line[1]);
                    a.y = position.y + std::stof(split_line[2]);
                    a.z = position.z + std::stof(split_line[3]);
                    temp_normals.push_back(a);
                }
            }
            else if (line[0] == 'f')
            {
                std::vector<std::string> tmp_split;
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

                tmp_split = split(split_line[1], "/");
                vertexIndex[0] = atoi(tmp_split[0]);

                tmp_split = split(split_line[2], "/");
                vertexIndex[1] = atoi(tmp_split[0]);

                tmp_split = split(split_line[3], "/");
                vertexIndex[2] = atoi(tmp_split[0]);

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                std::cout << std::endl;
                if (vertexIndices.size() % 36 == 0)
                    std::cout << std::endl;

                //uvIndices.push_back(uvIndex[0]);
                //uvIndices.push_back(uvIndex[1]);
                //uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }

        for(unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex - 1];
            glm::vec3 normal = temp_normals[vertexIndex - 1];
            vertices.push_back(vertex);
            normals.push_back(normal);
        }

        for (unsigned int i = 0; i < vertices.size(); i++)
        {
            colors.push_back(color);
        }

        if (glIsBuffer(vbo) == GL_TRUE)
        glDeleteBuffers(1, &vbo);
        if (glIsVertexArray(vao) == GL_TRUE)
            glDeleteVertexArrays(1, &vao);

        int vbo_size = vertices.size() * sizeof(vertices[0]) + colors.size() * sizeof(colors[0]) + normals.size() * sizeof(normals[0]);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vbo_size, 0, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vertices[0]), &vertices[0]);
            glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), colors.size() * sizeof(colors[0]), &colors[0]);
            glBufferSubData(GL_ARRAY_BUFFER, vbo_size - normals.size() * sizeof(normals[0]), normals.size() * sizeof(normals[0]), &normals[0]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(vertices[0])));
                glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
    else
        std::cout << filename << " not found !" << std::endl;
}

void OBJLoader::draw(glm::mat4 *model_view, glm::mat4 *projection)
{
    glUseProgram(shader.getProgramID());
        glBindVertexArray(vao);

            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(*projection));
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(*model_view));

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glBindVertexArray(0);
    glUseProgram(0);
}

std::vector<std::string> OBJLoader::split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back(s.substr (pos_start));
    return res;
}

int OBJLoader::atoi(std::string str)
{
    int nb = 0;
    int is_negative = 1;
    unsigned int i = 0;

    if (str[0] == '-')
    {
        is_negative *= -1;
        i = 1;
    }

    for(; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            nb *= 10;
            nb += str[i] - '0';
        }
    }
    return nb * is_negative;
}

void OBJLoader::set_color(glm::vec3 colors_tmp)
{
    color = colors_tmp;
}

void OBJLoader::set_position(glm::vec3 position_tmp)
{
    position = position_tmp;
}
