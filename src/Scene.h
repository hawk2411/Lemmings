#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "GameState.h"
#include <glm/glm.hpp>
#include <vector>
#include "MaskedTexturedQuad.h"
#include "Level.h"
#include "UI.h"
#include "Word.h"
#include "MaskManager.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene : public GameState {

public:

    static Scene &getInstance() {
        static Scene instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    };

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

    void setMaskManager(MaskManager *maskManager);

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

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    void update();

    void keyPressed(int key) override;

    void keyReleased(int key) override;

    void specialKeyPressed(int key) override;

    void specialKeyReleased(int key) override;

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

    std::unique_ptr<MaskedTexturedQuad> map;

    MaskManager *maskManager = nullptr;
    int posX=0, posY=0;

    MouseStates mouseState = MouseStates::NONE;
    ScreenMovedArea screenMovedArea = NONE_AREA;

};

#endif // _SCENE_INCLUDE

