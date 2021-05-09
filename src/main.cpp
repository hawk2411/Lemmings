#include <GL/glew.h>
#include <GL/glut.h>
#include <ctime>
#include <random>
#include "Game.h"


//Remove console (only works in Visual Studio)
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int Game::prevTime {0};

int main(int argc, char **argv) {
    srand(time(0));

    // GLUT initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow(argv[0]);
    glutSetWindowTitle("Lemmings");

    glutSetCursor(GLUT_CURSOR_NONE);

    glutDisplayFunc(Game::drawCallback);
    glutIdleFunc(Game::idleCallback);
    glutKeyboardFunc(Game::keyboardDownCallback);
    glutKeyboardUpFunc(Game::keyboardUpCallback);
    glutSpecialFunc(Game::specialDownCallback);
    glutSpecialUpFunc(Game::specialUpCallback);
    glutMouseFunc(Game::mouseCallback);
    glutMotionFunc(Game::motionCallback);
    glutPassiveMotionFunc(Game::motionCallback);

    // GLEW will take care of OpenGL extension functions
    glewExperimental = GL_TRUE;
    glewInit();

    // Game instance initialization
    Game::instance().init();
    Game::prevTime = glutGet(GLUT_ELAPSED_TIME);

    // GLUT gains control of the application
    glutMainLoop();

    return 0;
}



