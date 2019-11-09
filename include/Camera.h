#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>

#include <iostream>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <cmath>

class Camera
{
    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical);

        void update();
        void lookAt(glm::mat4 &model_view);
        void set_speed(float x);
        void set_aim_point(glm::vec3 point);
        void set_position(glm::vec3 pos);
        void move_at_ex_position();

        glm::vec3 get_position() const;

    private:
        glm::vec3 orientation;
        glm::vec3 vertical_axis;
        glm::vec3 lateral_movement;

        glm::vec3 position;
        glm::vec3 ex_position;
        glm::vec3 aim_center;

        float phi;
        float teta;

        sf::Vector2i ex_mouse_pos;

        float sensitivity;
        float speed;

        sf::Mouse mouse;
};

#endif // CAMERA_H
