#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "GameState.h"
#include "ParticleSystemManager.h"
#include "Difficulties.h"
#include "MaskedTexturedQuad.h"
#include "LevelIndex.h"
#include "UserInterface.h"
#include "Word.h"
#include "IMaskManager.h"
#include "Cursor.h"
#include "LevelRunner.h"
#include "JobAssigner.h"
#include "Scroller.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

struct ResultStatistic {
    int goalPercentage = 0;
    int currentPercentage = 0;
};

class Scene : public GameState {

public:

    Scene(Game *game, const LevelIndex& levelIndex);

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void eraseMask(int x, int y);

    void applyMask(int x, int y);

    void eraseSpecialMask(int x, int y);

    void applySpecialMask(int x, int y);

    void buildStep(glm::vec2 position);

    void changePauseStatus();

    void changeSpeedUpStatus();

    bool isPaused() const;

    bool isSpeedUp() const;

    unsigned char getPixel(int x, int y);


    VariableTexture &getMaskedMap();

    enum ScreenClickedArea {
        MAP,
        UI
    };

    enum ScreenMovedArea {
        SCROLL_AREA_LEFT,
        SCROLL_AREA_RIGHT,
        LEVEL,
        NONE_AREA
    };


    enum MouseStates {
        NONE,
        LEFT_MOUSE_PRESSED,
        RIGHT_MOUSE_PRESSED
    };

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;

    void changeLevel(const LevelIndex &levelIndex);

private:
    static ScreenClickedArea getClickedScreenArea(int mouseX, int mouseY);

    static ScreenMovedArea getMovedScreenArea(int mouseX, int mouseY);

    void leftClickOnUI(int posX, int posY);

    void leftClickOnMap(int posX, int posY);

    void updateCursorPosition();

    void initMap();

    void initUI();

    void updateCursor();

    void updateUI();

    void activateButton(int buttonIndex);

    inline int getSelectedButtonJobCount();

    //region private fields
private:
    bool _paused = false;
    bool _speedUp = false;

    std::unique_ptr<MaskedTexturedQuad> _map;

    std::map<Difficulties::Mode, std::unique_ptr<IMaskManager>> _maskManagers;
    Difficulties::Mode _currentDifficultyMode;

    int _posX=0, _posY=0;

    MouseStates _mouseState = MouseStates::NONE;
    ScreenMovedArea _screenMovedArea = NONE_AREA;

    std::unique_ptr<LevelRunner> _levelRunner;
    Cursor _cursor;
    UserInterface _ui;
    JobAssigner _jobAssigner;
    ParticleSystemManager _particleSystemManager;
    Scroller _scroller;
    ShaderManager* _shaderManager;
    //endregion
};

#endif // _SCENE_INCLUDE

