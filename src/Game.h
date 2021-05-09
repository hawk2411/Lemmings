#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Menu.h"
#include "SoundManager.h"
#include "MouseManager.h"
#include "KeyboardManager.h"
#include "GameState.h"
#include "ShaderManager.h"

const float TIME_PER_FRAME = 1000.f / 30.f; // Approx. 30 fps;

class Game {
private:
    SoundManager soundManager;
    bool bPlay; // Continue to play game?
    bool hardMode;
    GameState *gameState;

    std::unique_ptr<Sprite> hardModeIndicator;

    struct SpriteSheets {
        Texture cursorSprites;
        Texture lemmingAnimations;
        Texture rotatedLemmingAnimations;
        Texture doorSprites;
        Texture trapdoorSprites;
        Texture numSprites;
        Texture greenNumSprites;
        Texture purpleNumSprites;
        Texture buttonSprites;
        Texture jobNamesSprites;
        Texture infoWordSprites;
        Texture resultsWordSprites;
        Texture stepSprite;
        Texture greenNumLetters;
        Texture keySprites;
        Texture particleSprites;
        Texture skullSprite;
    };

public:
    /*
     * Constructor / Destructor
     */
    Game() : bPlay(true), hardMode(false), gameState(nullptr), hardModeIndicator(nullptr) {}

    //******************************************************************************************

    /*
     * Static members and functions
     *
     *  Game is a singleton (a class with a single instance) that represents our whole application
s     */
private:
    static void initSpriteSheets();

public:
    static Game &instance() {
        static Game G;

        return G;
    }

    static int prevTime;

    static SpriteSheets &spriteSheets() {
        static SpriteSheets spriteSheets;

        return spriteSheets;
    }

    static void mouseCallback(int button, int state, int x, int y);

    static void drawCallback() {
        Game::instance().render();
        glutSwapBuffers();
    }

    static void idleCallback() {
        int currentTime = glutGet(GLUT_ELAPSED_TIME);
        int deltaTime = currentTime - Game::prevTime;

        if (static_cast<float>(deltaTime) > TIME_PER_FRAME) {
            // Every time we enter here is equivalent to a game loop execution
            if (!Game::instance().update(deltaTime))
                exit(0);
            Game::prevTime = currentTime;
            glutPostRedisplay();
        }
    }

    // If a key is pressed this callback is called
    static void keyboardDownCallback(unsigned char key, int x, int y) {
        Game::instance().getGameState()->keyPressed(key);
    }

    // If a key is released this callback is called
    static void keyboardUpCallback(unsigned char key, int x, int y) {
        Game::instance().getGameState()->keyReleased(key);
    }

    // If a special key is pressed this callback is called
    static void specialDownCallback(int key, int x, int y) {
        Game::instance().getGameState()->specialKeyPressed(key);
    }

    // If a special key is released this callback is called
    static void specialUpCallback(int key, int x, int y) {
        Game::instance().getGameState()->specialKeyReleased(key);
    }

    // Same for changes in mouse cursor position
    static void motionCallback(int x, int y) {
        Game::instance().getGameState()->mouseMove(x, y);
    }
    // ******************static members end ************************************************************
    // *************************************************************************************************

    void init();

    bool update(int deltaTime);

    void render();

    void changeBplay();

    bool isHardMode() const;

    void swapDifficultyMode();

    const SoundManager *getSoundManager() const;

    GameState *getGameState();

    void setGameState(GameState *state);

};


#endif // _GAME_INCLUDE


