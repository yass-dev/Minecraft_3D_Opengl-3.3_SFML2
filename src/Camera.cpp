#include "Camera.h"

Camera::Camera()
    :   phi(0.0), teta(0.0), orientation(), vertical_axis(glm::vec3(0.0, 1.0, 0.0)), lateral_movement(),
        position(glm::vec3(-1, 1.5, -2)), aim_center(), speed(2)
{

}

Camera::Camera(glm::vec3 position_tmp, glm::vec3 pointCible, glm::vec3 axeVertical)
    :   phi(0.0), teta(0.0), orientation(), vertical_axis(axeVertical), lateral_movement(),
        position(position_tmp), aim_center(pointCible)
{

}

void Camera::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        ex_position = position;
        position = position + orientation * speed / 10.0f;
        aim_center = position + orientation;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        ex_position = position;
        position = position - orientation * speed / 10.0f;
        aim_center = position + orientation;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        ex_position = position;
        position = position + lateral_movement * speed / 10.0f;
        aim_center = position + orientation;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        ex_position = position;
        position = position - lateral_movement * speed / 10.0f;
        aim_center = position + orientation;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        speed += 0.1f;

    phi += (ex_mouse_pos.y - mouse.getPosition().y) * 0.5;
    teta += (ex_mouse_pos.x - mouse.getPosition().x) * 0.5;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        std::cout << "POSITION : x=" << position.x << " ; y=" << position.y << " ; z=" << position.z << std::endl;
        std::cout << "AIM : x=" << aim_center.x << " ; y=" << aim_center.y << " ; z=" << aim_center.z << std::endl;
        std::cout << "PHI : " << phi << " TETA : " << teta << std::endl;
    }

    if (phi > 89.0)
        phi = 89.0;
    else if (phi < -89.0)
        phi = -89.0;

    float phi_rad = phi * M_PI / 180;
    float teta_rad = teta  * M_PI / 180;

    if (vertical_axis.x == 1.0)
    {
        orientation.x = std::cos(phi_rad) * std::sin(teta_rad);
        orientation.y = std::cos(phi_rad) * std::cos(teta_rad);
        orientation.z = std::sin(phi_rad);
    }
    else if (vertical_axis.y == 1.0)
    {
        orientation.x = std::cos(phi_rad) * std::sin(teta_rad);
        orientation.y = std::sin(phi_rad);
        orientation.z = std::cos(phi_rad) * std::cos(teta_rad);
    }
    else
    {
        orientation.x = std::cos(phi_rad) * std::cos(teta_rad);
        orientation.y = std::cos(phi_rad) * std::sin(teta_rad);
        orientation.z = std::sin(phi_rad);
    }

    lateral_movement = glm::cross(vertical_axis, orientation);
    lateral_movement = glm::normalize(lateral_movement);
    aim_center = position + orientation;

    ex_mouse_pos = mouse.getPosition();
}

void Camera::lookAt(glm::mat4 &model_view)
{
    model_view = glm::lookAt(position, aim_center, vertical_axis);
}

void Camera::set_speed(float x)
{
    speed = x;
}

void Camera::set_aim_point(glm::vec3 point)
{
    orientation = point - position;
    orientation = glm::normalize(orientation);

    if (vertical_axis.x == 1.0)
    {
        phi = std::asin(orientation.x);
        teta = std::acos(orientation.y / std::cos(phi));

        if (orientation.y < 0)
            teta *= -1;
    }
    else if(vertical_axis.y == 1.0)
    {
        phi = std::asin(orientation.y);
        teta = std::acos(orientation.z / std::cos(phi));

        if (orientation.z < 0)
            teta *= -1;
    }
    else
    {
        phi = std::asin(orientation.x);
        teta = std::acos(orientation.z / std::cos(phi));

        if (orientation.z < 0)
            teta *= -1;
    }

    phi = phi * 180 / M_PI;
    teta = teta * 180 / M_PI;
}

void Camera::set_position(glm::vec3 pos)
{
    position = pos;
}

glm::vec3 Camera::get_position() const
{
    return position;
}

void Camera::move_at_ex_position()
{
    position = ex_position;
}
