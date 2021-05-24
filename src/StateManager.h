#ifndef _STATEMANAGER_INCLUDE
#define _STATEMANAGER_INCLUDE
#include <map>
#include "ShaderManager.h"
#include "GameState.h"

struct States {
    enum class Type {
        Menu = 0,
        Scene = 1,
        SceneInfo = 2,
        Result = 3,
        Instruction = 4,
        Credits = 5
    };
};

class StateManager {

public:
    explicit StateManager(Game *game, ShaderManager *shaderManager);

    void changeMenu();
//
    void changeInfo(LevelModes::Mode levelMode, int levelNum);
//
    void changeScene(LevelModes::Mode levelMode, int levelNum);
//
    void changeResults(int goalPercentage, int currentPercentage);
//
    void changeCredits();
//
    void changeInstructions();

    void update(int deltaTime);

    void render();

    GameState* getCurrentGameState();

    void setCurrentState(States::Type current);

    void onKeyPressed(const SDL_KeyboardEvent &event);

    void onMouseMove(const SDL_MouseMotionEvent &mouseMotionEvent);

    void onMouseButtonDown(const SDL_MouseButtonEvent &mouseButtonEvent);

    void onMouseButtonUp(const SDL_MouseButtonEvent &mouseButtonEvent);

    void onUserEvent(const SDL_UserEvent &event);

private:
    std::map <States::Type, unique_ptr<GameState>> _gameStates;
    States::Type _currentState;
    ShaderManager *_shaderManager;
};


#endif // _STATEMANAGER_INCLUDE