#include "Menu.h"
#include "InfoLevel.h"
#include "Scene.h"
#include "Results.h"
#include "Credits.h"
#include "Instructions.h"
#include "Game.h"
#include "StateManager.h"
#include "LevelRunner.h"

StateManager::StateManager(Game* game) :_currentState(States::Type::Menu), _game(game) {
    _gameStates.insert( std::make_pair(States::Type::Menu, unique_ptr<GameState>(new Menu(game))));
    _gameStates.insert( std::make_pair(States::Type::Scene, unique_ptr<GameState>(new Scene(game))));
    _gameStates.insert( std::make_pair(States::Type::SceneInfo, unique_ptr<GameState>(new InfoLevel(game))));
    _gameStates.insert( std::make_pair(States::Type::Result, unique_ptr<GameState>(new Results(game))));
    _gameStates.insert( std::make_pair(States::Type::Instruction, unique_ptr<GameState>(new Instructions(game))));
    _gameStates.insert( std::make_pair(States::Type::Credits, unique_ptr<GameState>(new Credits(game))));
}

void StateManager::changeMenu() {
    _currentState = States::Type::Menu;
    _gameStates[_currentState]->init();

}

void StateManager::changeInfo(int levelMode, int levelNum) {
    _currentState=States::Type::SceneInfo;
    _gameStates[_currentState]->init();
    dynamic_cast<InfoLevel*>(_gameStates[_currentState].get())->setLevel(levelMode, levelNum);

}

void StateManager::changeScene(int levelMode, int levelNum) {
    _currentState= States::Type::Scene;
    string modeName;
    switch (levelMode) {
        case FUN_MODE:
            modeName = "fun";
            break;
        case TRICKY_MODE:
            modeName = "tricky";
            break;
        case TAXING_MODE:
            modeName = "taxing";
            break;
        default:
            return;
    }
    auto *scene = dynamic_cast<Scene*>(_gameStates[_currentState].get());
    scene->setLevel(levelMode, levelNum);;
    scene->setGameMode(_game->getGameMode());


    _gameStates[_currentState]->init();

}

void StateManager::changeResults(int goalPercentage, int currentPercentage) {
    dynamic_cast<Results*>(_gameStates[States::Type::Result].get())->setPercentages(goalPercentage, currentPercentage);
    _gameStates[States::Type::Result]->init();
    _currentState = States::Type::Result
}

void StateManager::changeCredits() {
    _currentState = States::Type::Credits;
    _gameStates[_currentState]->init();
}

void StateManager::changeInstructions() {
    _currentState = States::Type::Instruction;
    _gameStates[_currentState]->init();
}

GameState *StateManager::getCurrentGameState() {
    return _gameStates[_currentState].get();
}

GameState *StateManager::getGameState(States::Type key_type) {
    return _gameStates[key_type].get();
}


