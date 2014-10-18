#ifndef GUN_GAME_OBJECT_FACTORY_H
#define GUN_GAME_OBJECT_FACTORY_H

#include <SFML\Graphics.hpp>

#include "ObjectClass.h"
#include "SpriteKey.h"

namespace gun
{
	class GameObject;

	class GameObjectFactory
	{
	public:
		static void Spawn(const ObjectClass::Enum object_class, 
			const sf::Vector2f& position);
		static GameObject* CreateGameObject(const std::string& object_class, 
			const sf::Vector2f& position);
		static GameObject* CreateGameObject(const ObjectClass::Enum object_class, 
			const sf::Vector2f& position);
		static GameObject* CreatePlayer(const sf::Vector2f& position);
		static GameObject* CreatePlayerBullet(const sf::Vector2f& position);
		static GameObject* CreateGrunt(const sf::Vector2f& position);
		static GameObject* CreateGib(ObjectClass::Enum object_class, 
			const sf::Vector2f& position, SpriteKey::Enum sprite_key);
		static GameObject* CreateDrone(const sf::Vector2f& position);
		static GameObject* CreateDroneBullet(const sf::Vector2f& position);
		static GameObject* CreateExploder(const sf::Vector2f& position);
		static GameObject* CreateDeathArrow(const sf::Vector2f& position, float rotation);
		static GameObject* CreateSplitter(const sf::Vector2f& position, float scale, int iteration);
		static GameObject* CreateExplosion(const sf::Vector2f& position, SpriteKey::Enum sprite_key);
		static GameObject* CreateSpeedPowerUp(const sf::Vector2f& position);
		static GameObject* CreateFireRatePowerUp(const sf::Vector2f& position);
		static GameObject* CreateGhostingPowerUp(const sf::Vector2f& position);

	private:
		static std::vector<sf::FloatRect> CalculateBounds(const GameObject* game_object);
	};
}

#endif