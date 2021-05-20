#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "StateManager.h"
#include "Difficulties.h"

const float TIME_PER_FRAME = 1000.f / 30.f; // Approx. 30 fps;


class Game {

public:
    /*
     * Constructor / Destructor
     */
    explicit Game();

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

    void onKeyPressed(const SDL_KeyboardEvent &event) {
        _stateManager->onKeyPressed(event);
    }

    void onMousMove(const SDL_MouseMotionEvent &mouseMotionEvent) {
        _stateManager->onMouseMove(mouseMotionEvent);
    }

    void onMouseButtonDown(const SDL_MouseButtonEvent &mouseButtonEvent) {
        _stateManager->onMouseButtonDown(mouseButtonEvent);
    }

    void onMouseButtonUp(const SDL_MouseButtonEvent &mouseButtonEvent) {
        _stateManager->onMouseButtonUp(mouseButtonEvent);
    }

    //******************************************************************************************

    /*
     * Static members and functions
     *
     *  Game is a singleton (a class with a single instance) that represents our whole application
s     */
    void onUserEvent(const SDL_UserEvent &event);

private:
    static void initSpriteSheets();

public:


    // ******************static members end ************************************************************

//    static Game *instance();

    static SpriteSheets &spriteSheets() {
        static SpriteSheets spriteSheets;

        return spriteSheets;
    }

    // *************************************************************************************************

    void init();

    bool update(int deltaTime);

    void render();

    void changeBplay();

    Difficulties::Mode getDifficultyMode() const;

    void swapDifficultyMode();

    SoundManager *getSoundManager() const;

    StateManager *getStateManager();

private:
    unique_ptr<SoundManager> _soundManager;
    unique_ptr<StateManager> _stateManager;
    unique_ptr<ShaderManager> _shaderManager;

    bool bPlay; // Continue to play game?
    Difficulties::Mode _dmode;


    int prevTime;
    std::unique_ptr<Sprite> hardModeIndicator;


};


#endif // _GAME_INCLUDE


