#include "SceneOpenGL.h"

SceneOpenGL::SceneOpenGL()
    :   running(true), camera(vec3(-2.7, 3.6, -3.97), vec3(-2.23, 3.0, -3.32), vec3(0, 1, 0)), height(650), width(1300),
        cursor_sprite(), cursor_texture(), fps_text(), fps_font()
{
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    window.create(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);

    if (!cursor_texture.loadFromFile("img/cross.png", sf::IntRect(0, 1, 50, 50)))
        std::cout << "Error cursor not loaded"<< std::endl;
    cursor_texture.setSmooth(true);
    cursor_sprite.setColor(sf::Color::Black);
    cursor_sprite.setTexture(cursor_texture);
    cursor_sprite.setPosition(window.getSize().x / 2 - 25, window.getSize().y / 2 - 25);

    camera.set_speed(5);
    camera.set_aim_point(glm::vec3(0, 180, 0));

    if (!fps_font.loadFromFile("fonts/Iceland.ttf"))
        std::cout << "Cannot load Iceland.ttf" << std::endl;
    fps_text.setFont(fps_font);
    fps_text.setColor(sf::Color::Green);
    fps_text.setPosition(10, 0);

    GLenum initialisationGLEW( glewInit() );
    if(initialisationGLEW != GLEW_OK)
    {
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;
        running = false;
    }
}

SceneOpenGL::~SceneOpenGL()
{

}

void SceneOpenGL::init()
{
    sf::ContextSettings settings = window.getSettings();
    std::cout << "depth bits:" << settings.depthBits << std::endl;
    std::cout << "stencil bits:" << settings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
    std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

    projection = perspective(70.0, (double) window.getSize().x / window.getSize().y, 1.0, 100.0);
    modelView = mat4(1.0);
    camera.set_position(glm::vec3(0, 42, 0));

    glEnable(GL_DEPTH_TEST);
}

void SceneOpenGL::run()
{
    std::string tmp_fps;
    sf::Clock fps_clock;

    Map map;

    OBJLoader loader;
    loader.set_color(glm::vec3(0.7, 0.3, 1.0));
    loader.set_position(glm::vec3(10, 10, 10));
    loader.load("C:\\Users\\Yassou\\Desktop\\Yassine\\C++\\SDL3DMapTest\\models\\donuts.obj");
    OBJLoader loader2;
    loader2.set_color(glm::vec3(0.0, 0.70, 1.0));
    loader2.set_position(glm::vec3(-10, 10, -10));
    loader2.load("C:\\Users\\Yassou\\Desktop\\Yassine\\C++\\SDL3DMapTest\\models\\cube.obj");

    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                running = false;
            }
        }

        fps_text.setString(tmp_fps);
        tmp_fps = itoa(fps);
        tmp_fps.append(" FPS");
        fps_text.setString(tmp_fps);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (map.check_collision(camera.get_position()))
            camera.move_at_ex_position();

        camera.update();
        camera.lookAt(modelView);

        map.draw(&modelView, &projection);
        loader.draw(&modelView, &projection);
        loader2.draw(&modelView, &projection);

        window.pushGLStates();
        window.resetGLStates();
            window.draw(cursor_sprite);
            window.draw(fps_text);
        window.popGLStates();
        glFlush();

        window.display();

        sf::Time time = fps_clock.restart();;
        fps = static_cast<int>(1 / time.asSeconds());
    }
}

std::string SceneOpenGL::itoa(int nb)
{
    std::string s;
    std::stringstream out;
    out << nb;
    s = out.str();
    return s;
}
