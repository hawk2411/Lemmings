#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "Scene.h"
#include "Menu.h"
#include "SoundManager.h"
#include "IMouseManager.h"
#include "IKeyboardManager.h"
#include "GameState.h"
#include "ShaderManager.h"
#include "StateManager.h"

const float TIME_PER_FRAME = 1000.f / 30.f; // Approx. 30 fps;


class Game {

public:
    /*
     * Constructor / Destructor
     */
    explicit Game();

    void keyboardDownCallback(const SDL_KeyboardEvent &event){
        gameState->onKeyPressed(event);
    }
    void onMousMove(const SDL_MouseMotionEvent& mouseMotionEvent){
        gameState->onMouseMove(mouseMotionEvent);
    }
    void onMouseButtonDown(const SDL_MouseButtonEvent& mouseButtonEvent) {
        gameState->onMouseButtonDown(mouseButtonEvent);
    }
    void onMouseButtonUp(const SDL_MouseButtonEvent& mouseButtonEvent) {
        gameState->onMouseButtonUp(mouseButtonEvent);
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

    bool isHardMode() const;

    void swapDifficultyMode();

    const SoundManager *getSoundManager() const;

    GameState *getGameState();

    void setGameState(States::Type state);

private:
    SoundManager soundManager;
    unique_ptr<StateManager> _stateManager;
    bool bPlay; // Continue to play game?
    bool hardMode;

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

};


#endif // _GAME_INCLUDE


