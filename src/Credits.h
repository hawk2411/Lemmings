#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"
#include "Game.h"

class Credits : public GameState {

public:
    explicit Credits(Game *game);
    ~Credits() override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void endMusic();

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

private:

    // Functions
    void initTextures();

    // Parametres
    Texture creditsLevelTexture;
    std::unique_ptr<Sprite> creditsLevelSprite;
    unique_ptr<Sound> music;
    ShaderManager *_shaderManager;
};


#endif