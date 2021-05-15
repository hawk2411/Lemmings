#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "GameState.h"
#include "Sprite.h"
#include "Sound.h"

class Menu : public GameState {

public:
    static Menu &getInstance() {
        static Menu instance;
        return instance;
    };

    Menu();

    ~Menu();

    void init();

    void update(int deltaTime);

    void render();

    void changeModeUp();

    void changeModeDown();

    int getMode();

    void endMusic();

private:

    // Functions

    void initTextures();

    void changeMode();

    // Parametres

    Texture menuTexture;
    Texture menuLogoTexture;
    Texture menuAboutTexture;
    Texture menuHelpTexture;
    Texture menuExitTexture;
    Texture menuModeTexture;
    Texture menuPlayingTexture;

    std::unique_ptr<Sprite> menuBackground;
    std::unique_ptr<Sprite> menuLogo;
    std::unique_ptr<Sprite> menuAbout;
    std::unique_ptr<Sprite> menuHelp;
    std::unique_ptr<Sprite> menuExit;
    std::unique_ptr<Sprite> menuMode;
    std::unique_ptr<Sprite> menuPlaying;

    int mode; // 0 = FUN, 1 = TRICKY, 2 = TAXING TODO change to enum

    float currentTime;

    glm::vec2 modePositions[3] = {
            glm::vec2(0, 0),
            glm::vec2(0, 0.25),
            glm::vec2(0, 0.5)
    };

    unique_ptr<Sound> music;
};


#endif