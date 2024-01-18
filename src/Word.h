#ifndef _WORD_INCLUDE
#define _WORD_INCLUDE

#include <vector>
#include "Sprite.h"
#include "ShaderManager.h"


class Word {

public:
    explicit Word(const string &word, ShaderManager *shaderManager);

    ~Word();

    void render();

    void setPosition(glm::vec2 position);

private:
    vector<std::unique_ptr<Sprite>> _letters;
    int _wordLength;
};


#endif // _WORD_INCLUDE

