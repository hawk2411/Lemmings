#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include "MusicFabric.hpp"
#include "ShaderManager.h"
#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Word.h"

class Instructions : public GameState {

public:
    Instructions(Game *game);
    ~Instructions() override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void passPageLeft();

    void passPageRight();

    static void endMusic();

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;


private:
    const int LINES_PAGE = 6;
    int actualPage;
    ShaderManager* _shaderManager;
    // Parametres
    Texture _instructionsLevelTexture;
    std::unique_ptr<Sprite> _instructionsLevelSprite;

    vector<unique_ptr<Word>> _instructionPages;

    std::unique_ptr<Sprite> _leftKey;
    std::unique_ptr<Sprite> _rightKey;
    std::unique_ptr<Sprite> _escapeKey;
    unique_ptr<Word> _instructionsWord;

    bool _onlyLeft;
    bool _onlyRight;

    music_ptr_t music_;
};


#endif // _INSTRUCTIONS_INCLUDE