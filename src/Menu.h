#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "GameState.h"
#include "Sprite.h"
#include "Sound.h"
#include "Game.h"
#include "LevelModes.h"

class Game;

class Menu : public GameState {

public:
    explicit Menu(Game *game);

    ~Menu() override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void changeModeUp();

    void changeModeDown();

    LevelModes::Mode getMode() const;

    void endMusic();


    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;


private:

    // Functions
    void initTextures();

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

    LevelModes::Mode _mode;

    glm::vec2 modePositions[3] = {
            glm::vec2(0, 0),
            glm::vec2(0, 0.25),
            glm::vec2(0, 0.5)
    };

    unique_ptr<Sound> music;
};


#endif