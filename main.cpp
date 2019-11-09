#include "SceneOpenGL.h"
#include "OBJLoader.h"

int main(int argc, char **argv)
{
    SceneOpenGL scene;
    scene.init();
    scene.run();

    return 0;
}
