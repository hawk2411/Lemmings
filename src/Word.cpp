#include "Word.h"
#include "LetterFactory.h"

Word::Word(string word) 
{
	wordLenght = word.size();
	lenght = 10 * wordLenght;
	letters = vector<Sprite*>(wordLenght);

	for (int i = 0; i < wordLenght; ++i) {
		letters[i] = LetterFactory::instance().createLetter(word[i]);
	}
}

Word::~Word()
{
	letters.clear();
}


void Word::render()
{
	for (int i = 0; i < wordLenght; ++i) {
		letters[i]->render();
	}
}

void Word::setPosititon(glm::vec2 positiona)
{
	position = positiona;

	for (int i = 0; i < wordLenght; ++i) {
		letters[i]->setPosition(position + glm::vec2(10 * i, 0));
	}
}


int Word::getLenght()
{
	return lenght;
}


