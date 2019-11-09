#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H

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
#include <sstream>

#include <thread>
#include <mutex>

#include "Shader.h"
#include "Cube.h"
#include "Ground.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Block.h"
#include "Map.h"

using namespace glm;

class SceneOpenGL
{
    public:
        SceneOpenGL();
        virtual ~SceneOpenGL();

        void init();
        void run();

    protected:

    private:
        std::string itoa(int nb);

        sf::ContextSettings settings;
        sf::RenderWindow window;
        sf::Sprite cursor_sprite;
        sf::Texture cursor_texture;

        Camera camera;

        mat4 modelView;
        mat4 projection;

        int height;
        int width;
        int fps;

        sf::Text fps_text;

        sf::Font fps_font;
        bool running;

        std::vector<Block*> vecBlock;
};

#endif // SCENEOPENGL_H
