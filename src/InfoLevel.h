#ifndef _INFOLEVEL_INCLUDE
#define _INFOLEVEL_INCLUDE

#include "Texture.h"
#include "Sprite.h"
#include "Word.h"
#include "IKeyboardManager.h"
#include "IMouseManager.h"

#include "GameState.h"
#include "Game.h"

class InfoLevel : public GameState{

public:
    explicit InfoLevel(Game* game);
    ~InfoLevel() override;

    // GameState override
    //===================================================================
    void init() override;

    void update(int deltaTime)override;

    void render()override;

    void setLevel(int level, int mode);
    //===================================================================
    //KeyboardManager override
    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;;

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    //===================================================================
    int getMode() const;

    int getLevel() const;


private:

    // Functions
    void initTextures();

    void initSprites();

    // Parametres
    Texture _infoLevelTexture;
    std::unique_ptr<Sprite> _infoLevelSprite;
    std::unique_ptr<Sprite> _leftKey;
    std::unique_ptr<Sprite> _rightKey;
    Word *_playWord{};
    Word *_menuWord{};

    int _mode{};
    int _level{};

};


#endif