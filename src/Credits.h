#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"

class Credits : public GameState {

public:
    static Credits &instance() {
        static Credits instance;
        return instance;
    };

    Credits();
    ~Credits() override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void endMusic();

    void keyPressed(int key) override;

    void keyReleased(int key) override;

    void specialKeyPressed(int key) override;

    void specialKeyReleased(int key) override;

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

private:

    // Functions
    void initTextures();

    // Parametres
    Texture creditsLevelTexture;
    std::unique_ptr<Sprite> creditsLevelSprite;
    unique_ptr<Sound> music;
};


#endif