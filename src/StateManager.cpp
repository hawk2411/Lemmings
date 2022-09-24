#include "UserEvent.h"
#include "Menu.h"
#include "InfoLevel.h"
#include "Scene.h"
#include "Results.h"
#include "Credits.h"
#include "Instructions.h"
#include "Game.h"

#include "StateManager.h"
#include "LevelIndex.h"

StateManager::StateManager(Game *game, ShaderManager *shaderManager) : _currentState(States::Type::Menu),
                                                                       _shaderManager(shaderManager) {

    LevelIndex levelIndex{LevelModes::Mode::FUN_MODE, 1};
    _gameStates.insert(std::make_pair(States::Type::Menu, unique_ptr<GameState>(new Menu(game, levelIndex))));
    _gameStates.insert(std::make_pair(States::Type::Scene, unique_ptr<GameState>(new Scene(game,
                                                                                           levelIndex))));
    _gameStates.insert(std::make_pair(States::Type::SceneInfo,
                                      unique_ptr<GameState>(new InfoLevel(game, levelIndex))));
    _gameStates.insert(std::make_pair(States::Type::Result, unique_ptr<GameState>(new Results(game, levelIndex))));
    _gameStates.insert(std::make_pair(States::Type::Instruction, unique_ptr<GameState>(new Instructions(game))));
    _gameStates.insert(std::make_pair(States::Type::Credits, unique_ptr<GameState>(new Credits(game))));
    setCurrentState(States::Type::Menu);
}

void StateManager::changeMenu() {
    _currentState = States::Type::Menu;
    _gameStates[_currentState]->init();

}

//
void StateManager::changeInfo(LevelModes::Mode levelMode, int levelNum) {
    _currentState = States::Type::SceneInfo;
    _gameStates[_currentState]->init();
    dynamic_cast<InfoLevel *>(_gameStates[_currentState].get())->setLevel(levelMode, levelNum);

}


void StateManager::changeScene(const LevelIndex &lvlIndex) {
    _currentState = States::Type::Scene;
    dynamic_cast<Scene *>(_gameStates[_currentState].get())->changeLevel(lvlIndex);
    _gameStates[_currentState]->init();
}

//
void StateManager::changeResults(ResultStatistic statistic, LevelIndex levelIndex) {
    if (_currentState == States::Type::Result) {
        return;
    }
    _currentState = States::Type::Result;
    auto *results = dynamic_cast<Results *>(_gameStates[_currentState].get());
    results->setPercentages(statistic.goalPercentage, statistic.currentPercentage);
    results->changeLevel(levelIndex);

    _gameStates[States::Type::Result]->init();
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

void StateManager::update(int deltaTime) {
    _gameStates[_currentState]->update(deltaTime);
}

void StateManager::render() {
    _gameStates[_currentState]->render();
}

void StateManager::setCurrentState(States::Type current) {
    _currentState = current;
    auto it_key = _gameStates.find(current);

    if (it_key == _gameStates.end()) {
        return;
    }
    _gameStates[current]->init();

}

void StateManager::onUserEvent(const SDL_UserEvent &event) {
    switch (event.code) {
        case CHANGE_TO_CREDITS:
            changeCredits();
            break;
        case CHANGE_TO_MENU:
            changeMenu();
            break;
        case CHANGE_TO_INSTRUCTION:
            changeInstructions();
            break;
        case CHANGE_TO_INFO: {
            UserEvent<CHANGE_TO_INFO, LevelIndex> changeToInfoEvent(event.data1);

            changeInfo(changeToInfoEvent.getData1()->mode, changeToInfoEvent.getData1()->levelNo);
        }
            break;
        case CHANGE_TO_SCENE: {
            UserEvent<CHANGE_TO_SCENE, LevelIndex> changeToSceneEvent(event.data1);

            changeScene(*changeToSceneEvent.getData1());
            break;
        }
        case CHANGE_TO_RESULT: {
            UserEvent<CHANGE_TO_RESULT, ResultStatistic, LevelIndex> ev(event.data1, event.data2);
            changeResults(*ev.getData1(), *ev.getData2());
            break;
        }
    }
}

void StateManager::onKeyPressed(const SDL_KeyboardEvent &event) {
    _gameStates[_currentState]->onKeyPressed(event);
}

void StateManager::onMouseMove(const SDL_MouseMotionEvent &mouseMotionEvent) {
    _gameStates[_currentState]->onMouseMove(mouseMotionEvent);
}

void StateManager::onMouseButtonDown(const SDL_MouseButtonEvent &mouseButtonEvent) {
    _gameStates[_currentState]->onMouseButtonDown(mouseButtonEvent);
}

void StateManager::onMouseButtonUp(const SDL_MouseButtonEvent &mouseButtonEvent) {
    _gameStates[_currentState]->onMouseButtonUp(mouseButtonEvent);
}





