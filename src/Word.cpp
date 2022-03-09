#include "Word.h"
#include "LetterFactory.h"
#include "ShaderManager.h"

Word::Word(const string &word, ShaderManager *shaderManager) {
    _wordLength = word.size();
    _letters = vector<std::unique_ptr<Sprite>>(_wordLength);

    for (int i = 0; i < _wordLength; ++i) {
        _letters[i] = std::move(LetterFactory::createLetter(word[i], shaderManager));
    }
}

Word::~Word() {
    _letters.clear();
}


void Word::render() {
    for (int i = 0; i < _wordLength; ++i) {
        _letters[i]->render();
    }
}

void Word::setPosition(glm::vec2 position) {
    position = position;

    for (int i = 0; i < _wordLength; ++i) {
        _letters[i]->setPosition(position + glm::vec2(10 * i, 0));
    }
}



