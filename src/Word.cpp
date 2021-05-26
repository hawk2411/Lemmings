#include "Word.h"
#include "LetterFactory.h"
#include "ShaderManager.h"

Word::Word(const string &word, ShaderManager *shaderManager) {
    wordLength = word.size();
    length = 10 * wordLength;
    letters = vector<std::unique_ptr<Sprite>>(wordLength);

    for (int i = 0; i < wordLength; ++i) {
        letters[i] = std::move(LetterFactory::createLetter(word[i], shaderManager));
    }
}

Word::~Word() {
    letters.clear();
}


void Word::render() {
    for (int i = 0; i < wordLength; ++i) {
        letters[i]->render();
    }
}

void Word::setPosition(glm::vec2 position) {
    position = position;

    for (int i = 0; i < wordLength; ++i) {
        letters[i]->setPosition(position + glm::vec2(10 * i, 0));
    }
}



