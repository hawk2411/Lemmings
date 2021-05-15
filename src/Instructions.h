#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Word.h"
#include "Sound.h"

#define LINESPAGE 6

class Instructions : public GameState {

public:
    static Instructions &getInstance() {
        static Instructions instance;
        return instance;
    };

    Instructions();
    ~Instructions() override;

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void passPageLeft();

    void passPageRight();

    void endMusic();

private:

    // Functions
    void initTextures();

    void initSprites();

    void initLines();

    int actualPage;

    // Parametres
    Texture _instructionsLevelTexture;
    std::unique_ptr<Sprite> _instructionsLevelSprite;

    vector<Word *> _instructionPages;

    std::unique_ptr<Sprite> _leftKey;
    std::unique_ptr<Sprite> _rightKey;
    std::unique_ptr<Sprite> _escapeKey;
    Word *_instructionsWord;

    bool _onlyLeft;
    bool _onlyRight;

    unique_ptr<Sound> _music;
};


#endif // _INSTRUCTIONS_INCLUDE