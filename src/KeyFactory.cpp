#include "Game.h"
#include "KeyFactory.h"
#include "ShaderManager.h"


std::unique_ptr<Sprite> KeyFactory::createLeftKey(glm::ivec2 size) {
	auto keySprite = Sprite::createSprite(size, glm::vec2(63./128, 36./128), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().keySprites);
	keySprite->setNumberAnimations(1);

	glm::vec2 textureCoord = glm::vec2(0.5, 0);

	keySprite->addKeyframe(0, textureCoord);
	keySprite->changeAnimation(0);

	return keySprite;

}

std::unique_ptr<Sprite> KeyFactory::createRightKey(glm::ivec2 size) {
	auto keySprite = Sprite::createSprite(size, glm::vec2(63. / 128, 36. / 128), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().keySprites);
	keySprite->setNumberAnimations(1);

	glm::vec2 textureCoord = glm::vec2(0, 0);

	keySprite->addKeyframe(0, textureCoord);
	keySprite->changeAnimation(0);

	return keySprite;
}

std::unique_ptr<Sprite> KeyFactory::createEscapeKey(glm::ivec2 size) {
	auto keySprite = Sprite::createSprite(size, glm::vec2(63. / 128, 36. / 128), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().keySprites);
	keySprite->setNumberAnimations(1);

	glm::vec2 textureCoord = glm::vec2(0, 0.5);

	keySprite->addKeyframe(0, textureCoord);
	keySprite->changeAnimation(0);

	return keySprite;
}