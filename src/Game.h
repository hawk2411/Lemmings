#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "ShaderManager.h"
#include "StateManager.h"
#include "Difficulties.h"

//const float TIME_PER_FRAME = 1000.f / 30.f; // Approx. 30 fps;


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
        stateManager_->onKeyPressed(event);
    }

    void onMousMove(const SDL_MouseMotionEvent &mouseMotionEvent) {
        stateManager_->onMouseMove(mouseMotionEvent);
    }

    void onMouseButtonDown(const SDL_MouseButtonEvent &mouseButtonEvent) {
        stateManager_->onMouseButtonDown(mouseButtonEvent);
    }

    void onMouseButtonUp(const SDL_MouseButtonEvent &mouseButtonEvent) {
        stateManager_->onMouseButtonUp(mouseButtonEvent);
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

    StateManager *getStateManager();

    ShaderManager *getShaderManager()const{return shaderManager_.get();}

private:
    unique_ptr<StateManager> stateManager_;
    unique_ptr<ShaderManager> shaderManager_;
    bool bPlay_; // Continue to play game?
    Difficulties::Mode dmode_;

    std::unique_ptr<Sprite> hardModeIndicator_;


};


#endif // _GAME_INCLUDE


