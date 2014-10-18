#ifndef GUN_SPRITE_CACHE_H
#define GUN_SPRITE_CACHE_H

#include "Sprite.h"
#include "TextureKey.h"
#include "SpriteKey.h"

namespace gun
{
	class SpriteCache
	{
	public:
		SpriteCache();

		Sprite GetSprite(SpriteKey::Enum sprite_key);

	private:
		std::map<int, Sprite> sprite_cache_;
		std::map<int, sf::Texture> texture_cache_;
		
		void LoadSprites();
		void LoadTextures();
		void LoadTexture(TextureKey::Enum textureKey, const std::string& file);
	};
}

#endif