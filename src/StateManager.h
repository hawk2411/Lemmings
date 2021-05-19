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

    void changeInfo(int levelMode, int levelNum);

    void changeScene(int levelMode, int levelNum);

    void changeResults(int goalPercentage, int currentPercentage);

    void changeCredits();

    void changeInstructions();

    States::Type getCurrentStateType()const{return _currentState;}
    void setCurrentState(States::Type type){_currentState = type;}

    GameState* getCurrentGameState();

    GameState* getGameState(States::Type key_type);
private:
    std::map <States::Type, unique_ptr<GameState>> _gameStates;
    States::Type _currentState;
    ShaderManager *_shaderManager;
};


#endif // _STATEMANAGER_INCLUDE