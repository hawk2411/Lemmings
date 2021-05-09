#ifndef _WORD_INCLUDE
#define _WORD_INCLUDE

#include <vector>
#include "Sprite.h"


class Word {

public:
    explicit Word(const string &word);

    ~Word();

    void render();

    void setPosition(glm::vec2 position);


private:
    glm::vec2 position;
    vector<std::unique_ptr<Sprite>> letters;

    int length;
    int wordLength;

};


#endif // _WORD_INCLUDE

