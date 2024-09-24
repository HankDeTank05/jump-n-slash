#include "../Engine Code/JumpSlashEngine.h"

#include "../Engine Code/TextureManager.h"
#include "../Engine Code/SpriteManager.h"

#include "TestScene.h"

void JumpSlashEngine::LoadResources()
{
	TextureManager::LoadTexture("tex test", "player/idle_1_32.png");

	SpriteManager::LoadSprite("spr test 1", TextureManager::GetTexture("tex test"));
	SpriteManager::LoadSprite("spr test 2", TextureManager::GetTexture("tex test"), sf::IntRect(0, 0, 16, 16));
	SpriteManager::LoadSprite("spr test 3", "tex test");
	SpriteManager::LoadSprite("spr test 4", "tex test", sf::IntRect(0, 0, 16, 16));

	JumpSlashEngine::SetStartScene(new TestScene());
}
