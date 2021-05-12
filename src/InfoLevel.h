#ifndef _INFOLEVEL_INCLUDE
#define _INFOLEVEL_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Word.h"

class InfoLevel : public GameState {

public:
    static InfoLevel &instance() {
        static InfoLevel instance;
        return instance;
    };

    void init() override;

    void update(int deltaTime)override;

    void render()override;

    void setLevel(int level, int mode);

    int getMode();

    int getLevel();

private:

    // Functions
    void initTextures();

    void initSprites();

    // Parametres
    Texture _InfoLevelTexture;
    std::unique_ptr<Sprite> _InfoLevelSprite;
    std::unique_ptr<Sprite> _leftKey;
    std::unique_ptr<Sprite> _rightKey;
    Word *_playWord;
    Word *_menuWord;

    int _mode;
    int _level;

};


#endif