#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "GameState.h"
#include <glm/glm.hpp>
#include <vector>
#include <map>

#include "Difficulties.h"
#include "MaskedTexturedQuad.h"
#include "UI.h"
#include "Word.h"
#include "IMaskManager.h"

#include "LevelRunner.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene : public GameState {

public:

    Scene(Game *game, SoundManager *soundManager );

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

    char getPixel(int x, int y);


    static VariableTexture &getMaskedMap();

    enum ScreenClickedArea {
        MAP,
        UI,
        INFO
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



    void update();

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;

    void setLevel(LevelModes::Mode mode, int i);

private:
    ScreenClickedArea getClickedScreenArea(int mouseX, int mouseY);

    ScreenMovedArea getMovedScreenArea(int mouseX, int mouseY);

    void leftClickOnUI(int posX, int posY);

    void leftClickOnMap(int posX, int posY);

    void updateCursorPosition();

    void initMap();

    void initUI();

    void updateUI();

    bool paused = false;
    bool speedUp = false;

    std::unique_ptr<MaskedTexturedQuad> _map;

    std::map<Difficulties::Mode, std::unique_ptr<IMaskManager>> _maskManagers;
    Difficulties::Mode _currentDifficultyMode;

    int posX=0, posY=0;

    MouseStates mouseState = MouseStates::NONE;
    ScreenMovedArea screenMovedArea = NONE_AREA;

    std::unique_ptr<LevelRunner> _levelRunner;


};

#endif // _SCENE_INCLUDE

