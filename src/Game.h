#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Menu.h"
#include "SoundManager.h"
#include "MouseManager.h"
#include "IKeyboardManager.h"
#include "GameState.h"
#include "ShaderManager.h"

const float TIME_PER_FRAME = 1000.f / 30.f; // Approx. 30 fps;

class Game {

private:
    SoundManager soundManager;
    bool bPlay; // Continue to play game?
    bool hardMode;
    GameState *gameState;

    int prevTime;
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
    explicit Game(int prevTime) : bPlay(true), hardMode(false),
                                  gameState(nullptr), hardModeIndicator(nullptr), prevTime(prevTime) {

    }

    //******************************************************************************************

    /*
     * Static members and functions
     *
     *  Game is a singleton (a class with a single instance) that represents our whole application
s     */
private:
    static void initSpriteSheets();
public:


    // ******************static members end ************************************************************

    static Game *instance();

    static SpriteSheets &spriteSheets() {
        static SpriteSheets spriteSheets;

        return spriteSheets;
    }

    static void mouseCallback(int button, int state, int x, int y);

    static void drawCallback();

    static void idleCallback();

    // If a key is pressed this callback is called
    static void keyboardDownCallback(unsigned char key, int x, int y);

    // If a key is released this callback is called
    static void keyboardUpCallback(unsigned char key, int x, int y);

    // If a special key is pressed this callback is called
    static void specialDownCallback(int key, int x, int y);

    // If a special key is released this callback is called
    static void specialUpCallback(int key, int x, int y);

    // Same for changes in mouse cursor position
    static void motionCallback(int x, int y);

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


