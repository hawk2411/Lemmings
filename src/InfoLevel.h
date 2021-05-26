#ifndef _INFOLEVEL_INCLUDE
#define _INFOLEVEL_INCLUDE

#include "Texture.h"
#include "Sprite.h"
#include "Word.h"
#include "IKeyboardManager.h"
#include "IMouseManager.h"

#include "LevelModes.h"
#include "GameState.h"
#include "Game.h"
#include "LevelIndex.h"

class InfoLevel : public GameState{

public:
    explicit InfoLevel(Game* game, const LevelIndex& index);
    ~InfoLevel() override;

    // GameState override
    //===================================================================
    void init() override;

    void update(int deltaTime)override;

    void render()override;

    void setLevel(LevelModes::Mode levelMode, int numLevel);
    //===================================================================
    //KeyboardManager override
    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;;

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    //===================================================================


private:

    // Functions
    void initTextures();

    // Parametres
    Texture _infoLevelTexture;
    std::unique_ptr<Sprite> _infoLevelSprite;
    std::unique_ptr<Sprite> _leftKey;
    std::unique_ptr<Sprite> _rightKey;
    std::unique_ptr<Word> _playWord;
    std::unique_ptr<Word> _menuWord;

    LevelIndex _levelIndex;
    ShaderManager* _shaderManager;
};


#endif