#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "GameState.h"
#include "Sprite.h"
#include "MusicFabric.hpp"
#include "Game.h"
#include "LevelModes.h"
#include "LevelIndex.h"

class Game;

class Menu : public GameState {

public:
    explicit Menu(Game *game, const LevelIndex &levelIndex);

    ~Menu() override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void changeModeUp();

    void changeModeDown();

    LevelModes::Mode getMode() const;

    static void endMusic();


    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;


private:

    // Functions
    void initTextures();

    // Parametres

    Texture _menuTexture;
    Texture _menuLogoTexture;
    Texture _menuAboutTexture;
    Texture _menuHelpTexture;
    Texture _menuExitTexture;
    Texture _menuModeTexture;
    Texture _menuPlayingTexture;

    std::unique_ptr<Sprite> _menuBackground;
    std::unique_ptr<Sprite> _menuLogo;
    std::unique_ptr<Sprite> _menuAbout;
    std::unique_ptr<Sprite> _menuHelp;
    std::unique_ptr<Sprite> _menuExit;
    std::unique_ptr<Sprite> _menuMode;
    std::unique_ptr<Sprite> _menuPlaying;

    LevelIndex _levelIndex;

    glm::vec2 _modePositions[3] = {
            glm::vec2(0, 0),
            glm::vec2(0, 0.25),
            glm::vec2(0, 0.5)
    };

    music_ptr_t _music;
    ShaderManager *_shaderManager;
};


#endif