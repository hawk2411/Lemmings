#include "Game.h"
#include "LetterFactory.h"
#include "ShaderManager.h"


std::unique_ptr<Sprite> LetterFactory::createLetter(char c) {
	auto letterSprite = Sprite::createSprite(glm::ivec2(9, 12), glm::vec2(18./32, 24./4096), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().greenNumLetters);
	letterSprite->setNumberAnimations(1);

	glm::vec2 textureCoord = glm::vec2(0, (26.*(c - '!'))/4096);

	letterSprite->addKeyframe(0, textureCoord);
	letterSprite->changeAnimation(0);

	return letterSprite;

}

