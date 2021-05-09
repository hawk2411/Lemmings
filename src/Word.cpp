#include "Word.h"
#include "LetterFactory.h"

Word::Word(const string &word) {
    wordLength = word.size();
    length = 10 * wordLength;
    letters = vector<std::unique_ptr<Sprite>>(wordLength);

    for (int i = 0; i < wordLength; ++i) {
        letters[i] = std::move(LetterFactory::instance().createLetter(word[i]));
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



