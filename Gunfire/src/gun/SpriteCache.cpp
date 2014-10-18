#include "SpriteCache.h"
#include "Paths.h"
#include "SpriteKey.h"
#include "AnimationLoader.h"

gun::SpriteCache::SpriteCache()
{
	LoadTextures();
	LoadSprites();
}

gun::Sprite gun::SpriteCache::GetSprite(SpriteKey::Enum sprite_key)
{
	return sprite_cache_[sprite_key];
}

void gun::SpriteCache::LoadSprites()
{
	sprite_cache_[SpriteKey::SPLASH] = Sprite(
		texture_cache_[TextureKey::SPLASH]);
	sprite_cache_[SpriteKey::SPLASH].set_origin(sf::Vector2f(0, 0));
	sprite_cache_[SpriteKey::SPLASH].set_position(sf::Vector2f(0, 0));
	sprite_cache_[SpriteKey::KID] = Sprite(
		texture_cache_[TextureKey::KID], 
		AnimationLoader::Load(Paths::ANIMATIONS_DIR + "kid.xml"), 0, 5);
	sprite_cache_[SpriteKey::PLAYER_BULLET] = Sprite(
		texture_cache_[TextureKey::PLAYER_BULLET]);
	sprite_cache_[SpriteKey::ZOMBIE] = Sprite(
		texture_cache_[TextureKey::ZOMBIE], 
		AnimationLoader::Load(Paths::ANIMATIONS_DIR + "zombie.xml"), 0, 5);
	sprite_cache_[SpriteKey::ZOMBIE_HEAD] = Sprite(
		texture_cache_[TextureKey::ZOMBIE_HEAD]);
	sprite_cache_[SpriteKey::ZOMBIE_ARM] = Sprite(
		texture_cache_[TextureKey::ZOMBIE_ARM]);
	sprite_cache_[SpriteKey::ZOMBIE_LEG] = Sprite(
		texture_cache_[TextureKey::ZOMBIE_LEG]);
	sprite_cache_[SpriteKey::DRONE] = Sprite(texture_cache_[TextureKey::DRONE]);
	sprite_cache_[SpriteKey::DRONE_BULLET] = Sprite(
		texture_cache_[TextureKey::DRONE_BULLET]);
	sprite_cache_[SpriteKey::BOMB] = Sprite(texture_cache_[TextureKey::BOMB]);
	sprite_cache_[SpriteKey::BLOB] = Sprite(texture_cache_[TextureKey::BLOB]);
	sprite_cache_[SpriteKey::DEATH_ARROW] = Sprite(texture_cache_[TextureKey::DEATH_ARROW]);
	sprite_cache_[SpriteKey::BLOOD] = Sprite(
		texture_cache_[TextureKey::BLOOD], 
		AnimationLoader::Load(Paths::ANIMATIONS_DIR + "blood.xml"), 0, 16);
	sprite_cache_[SpriteKey::EXPLOSION] = Sprite(
		texture_cache_[TextureKey::EXPLOSION], 
		AnimationLoader::Load(Paths::ANIMATIONS_DIR + "explosion.xml"), 0, 60);
	sprite_cache_[SpriteKey::WINGS] = Sprite(texture_cache_[TextureKey::WINGS]);
	sprite_cache_[SpriteKey::BULLETS] = Sprite(texture_cache_[TextureKey::BULLETS]);
	sprite_cache_[SpriteKey::GHOST] = Sprite(texture_cache_[TextureKey::GHOST]);
}

void gun::SpriteCache::LoadTextures()
{
	LoadTexture(TextureKey::SPLASH, Paths::TEXTURES_DIR + "splash.png");
	LoadTexture(TextureKey::KID, Paths::TEXTURES_DIR + "kid.png");
	LoadTexture(TextureKey::PLAYER_BULLET, Paths::TEXTURES_DIR + "bullet.png");
	LoadTexture(TextureKey::ZOMBIE, Paths::TEXTURES_DIR + "zombie.png");
	LoadTexture(TextureKey::ZOMBIE_HEAD, Paths::TEXTURES_DIR + "zombie_head.png");
	LoadTexture(TextureKey::ZOMBIE_ARM, Paths::TEXTURES_DIR + "zombie_arm.png");
	LoadTexture(TextureKey::ZOMBIE_LEG, Paths::TEXTURES_DIR + "zombie_leg.png");
	LoadTexture(TextureKey::DRONE, Paths::TEXTURES_DIR + "drone.png");
	LoadTexture(TextureKey::DRONE_BULLET, Paths::TEXTURES_DIR + "drone_bullet.png");
	LoadTexture(TextureKey::BOMB, Paths::TEXTURES_DIR + "bomb.png");
	LoadTexture(TextureKey::BLOB, Paths::TEXTURES_DIR + "blob.png");
	LoadTexture(TextureKey::DEATH_ARROW, Paths::TEXTURES_DIR + "death_arrow.png");
	LoadTexture(TextureKey::BLOOD, Paths::TEXTURES_DIR + "blood.png");
	LoadTexture(TextureKey::EXPLOSION, Paths::TEXTURES_DIR + "explosion.png");
	LoadTexture(TextureKey::WINGS, Paths::TEXTURES_DIR + "wings.png");
	LoadTexture(TextureKey::BULLETS, Paths::TEXTURES_DIR + "bullets.png");
	LoadTexture(TextureKey::GHOST, Paths::TEXTURES_DIR + "ghost.png");
}

void gun::SpriteCache::LoadTexture(
	TextureKey::Enum textureKey, const std::string& file)
{
	sf::Texture texture = sf::Texture();
	texture.loadFromFile(file);
	texture_cache_[textureKey] = texture;
}