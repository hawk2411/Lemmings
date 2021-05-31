#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include <memory>
#include <SDL_mixer.h>
#include <functional>
#include <sstream>

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

class Credits : public GameState {

public:
    explicit Credits(Game *game);
    ~Credits() override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    static void endMusic();

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

private:

    // Parametres
    Texture creditsLevelTexture;
    std::unique_ptr<Sprite> creditsLevelSprite;
    ShaderManager *_shaderManager;
    music_ptr_t music_;
};


#endif