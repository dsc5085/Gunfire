#include "GameObjectFactory.h"
#include "CollisionType.h"
#include "Math.h"
#include "VectorMath.h"
#include "PolygonMath.h"
#include "DiedEventArgs.h"
#include "GameObject.h"
#include "BoundingPart.h"
#include "TimedDeathPart.h"
#include "DieAfterAnimationPart.h"
#include "DieOnCollisionPart.h"
#include "DamageOnCollisionPart.h"
#include "AddPartOnCollisionPart.h"
#include "GhostPart.h"
#include "PlayerControllerPart.h"
#include "GruntControllerPart.h"
#include "DroneControllerPart.h"
#include "ExploderControllerPart.h"
#include "SplitterControllerPart.h"
#include "SpawnOnDiePart.h"
#include "BouncingPart.h"
#include "SpeedMultiplierPart.h"
#include "FireRateMultiplierPart.h"
#include "VelocityRandomizerPart.h"
#include "SpinnerPart.h"
#include "SoundOnDiePart.h"
#include "GravityPart.h"
#include "Services.h"
#include "SoundCache.h"
#include "SpriteCache.h"

void gun::GameObjectFactory::Spawn(
	const ObjectClass::Enum object_class, const sf::Vector2f& position)
{
	GameObject* game_object = CreateGameObject(object_class, position);
	game_object->Initialize();
	Services::Instance().object_manager()->MarkAdded(game_object);
}

gun::GameObject* gun::GameObjectFactory::CreateGameObject(
	const std::string& object_class, const sf::Vector2f& position)
{
	GameObject* game_object = 0;
	
	if (object_class == "GRUNT")
	{
		game_object = CreateGrunt(position);
	}
	else if (object_class == "DRONE")
	{
		game_object = CreateDrone(position);
	}
	else if (object_class == "EXPLODER")
	{
		game_object = CreateExploder(position);
	}
	else if (object_class == "SPLITTER")
	{
		game_object = CreateSplitter(position, 1.0, 2);
	}
	else
	{
		std::string message = object_class + " is not a valid object class.";
		throw std::invalid_argument(message);
	}

	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateGameObject(
	const ObjectClass::Enum object_class, const sf::Vector2f& position)
{
	GameObject* game_object = 0;

	switch (object_class)
	{
	case ObjectClass::PLAYER:
		game_object = CreatePlayer(position);
		break;
	case ObjectClass::PLAYER_BULLET:
		game_object = CreatePlayerBullet(position);
		break;
	case ObjectClass::GRUNT:
		game_object = CreateGrunt(position);
		break;
	case ObjectClass::GRUNT_HEAD:
		game_object = CreateGib(ObjectClass::GRUNT_HEAD, position, SpriteKey::ZOMBIE_HEAD);
		break;
	case ObjectClass::GRUNT_ARM:
		game_object = CreateGib(ObjectClass::GRUNT_ARM, position, SpriteKey::ZOMBIE_ARM);
		break;
	case ObjectClass::GRUNT_LEG:
		game_object = CreateGib(ObjectClass::GRUNT_LEG, position, SpriteKey::ZOMBIE_LEG);
		break;
	case ObjectClass::DRONE:
		game_object = CreateDrone(position);
		break;
	case ObjectClass::DRONE_BULLET:
		game_object = CreateDroneBullet(position);
		break;
	case ObjectClass::EXPLODER:
		game_object = CreateExploder(position);
		break;
	case ObjectClass::SPLITTER:
		game_object = CreateSplitter(position, 1.0, 2);
		break;
	case ObjectClass::BLOOD:
		game_object = CreateExplosion(position, SpriteKey::BLOOD);
		break;
	case ObjectClass::EXPLOSION:
		game_object = CreateExplosion(position, SpriteKey::EXPLOSION);
		break;
	case ObjectClass::SPEED_POWER_UP:
		game_object = CreateSpeedPowerUp(position);
		break;
	case ObjectClass::FIRE_RATE_POWER_UP:
		game_object = CreateFireRatePowerUp(position);
		break;
	case ObjectClass::GHOSTING_POWER_UP:
		game_object = CreateGhostingPowerUp(position);
		break;
	default:
		std::string message = object_class + " is not a valid object class.";
		throw std::invalid_argument(message);
	}

	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreatePlayer(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::KID);
	GameObject* game_object = new GameObject(ObjectClass::PLAYER, sprite, position);
	game_object->set_coll_type(CollisionType::PLAYER);
	game_object->max_speed() = 7;
	game_object->Attach(new PlayerControllerPart());
	game_object->Attach(new BoundingPart(Services::Instance().level().area));
	game_object->Attach(new GhostPart(3));
	game_object->Attach(new DieOnCollisionPart(CollisionType::ENEMY));
	game_object->Attach(new SoundOnDiePart(SoundKey::PAIN));
	std::vector<GameObject*> spawns = std::vector<GameObject*>();
	spawns.push_back(CreateGameObject(ObjectClass::BLOOD, sf::Vector2f(0, 0)));
	game_object->Attach(new SpawnOnDiePart(spawns));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreatePlayerBullet(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::PLAYER_BULLET);
	GameObject* game_object = new GameObject(ObjectClass::PLAYER_BULLET, sprite, position);
	game_object->Attach(new TimedDeathPart(0.5));
	game_object->Attach(new DieOnCollisionPart(CollisionType::ENEMY));
	game_object->Attach(new DamageOnCollisionPart(CollisionType::ENEMY, 50));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateGrunt(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::ZOMBIE);
	GameObject* game_object = new GameObject(ObjectClass::GRUNT, sprite, position, 100);
	game_object->health() = 100;
	game_object->set_coll_type(CollisionType::ENEMY);
	game_object->max_speed() = 4;
	game_object->Attach(new GruntControllerPart());
	game_object->Attach(new DieOnCollisionPart(CollisionType::PLAYER));
	game_object->Attach(new SoundOnDiePart(SoundKey::ZOMBIE_ATTACKED));
	game_object->Attach(new BoundingPart(CalculateBounds(game_object)));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateGib(ObjectClass::Enum object_class, 
	const sf::Vector2f& position, SpriteKey::Enum sprite_key)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(sprite_key);
	GameObject* game_object = new GameObject(object_class, sprite, position);
	game_object->Attach(new GravityPart());
	game_object->Attach(new TimedDeathPart(10));
	game_object->Attach(new SpinnerPart(720));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateDrone(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::DRONE);
	GameObject* game_object = new GameObject(ObjectClass::DRONE, sprite, position, 200);
	game_object->health() = 50;
	game_object->set_coll_type(CollisionType::ENEMY);
	game_object->max_speed() = 5;
	game_object->Attach(new DroneControllerPart());
	game_object->Attach(new DieOnCollisionPart(CollisionType::PLAYER));
	game_object->Attach(new BoundingPart(CalculateBounds(game_object)));
	game_object->Attach(new SoundOnDiePart(SoundKey::ARCADE_EXPLOSION));
	std::vector<GameObject*> spawns = std::vector<GameObject*>();
	spawns.push_back(CreateGameObject(ObjectClass::EXPLOSION, sf::Vector2f(0, 0)));
	game_object->Attach(new SpawnOnDiePart(spawns));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateDroneBullet(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::DRONE_BULLET);
	GameObject* game_object = new GameObject(ObjectClass::DRONE_BULLET, sprite, position);
	game_object->Attach(new TimedDeathPart(5));
	game_object->Attach(new DieOnCollisionPart(CollisionType::PLAYER));
	game_object->Attach(new DamageOnCollisionPart(CollisionType::PLAYER, 50));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateExploder(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::BOMB);
	GameObject* game_object = new GameObject(ObjectClass::EXPLODER, sprite, position, 200);
	game_object->health() = 150;
	game_object->set_coll_type(CollisionType::ENEMY);
	game_object->max_speed() = 4;
	game_object->Attach(new DieOnCollisionPart(CollisionType::PLAYER));
	game_object->Attach(new BouncingPart());
	game_object->Attach(new VelocityRandomizerPart());
	game_object->Attach(new ExploderControllerPart(5, 20));
	game_object->Attach(new BoundingPart(CalculateBounds(game_object)));
	std::vector<GameObject*> spawns = std::vector<GameObject*>();
	spawns.push_back(CreateGameObject(ObjectClass::EXPLOSION, sf::Vector2f(0, 0)));
	game_object->Attach(new SpawnOnDiePart(spawns));
	game_object->Attach(new SoundOnDiePart(SoundKey::ARCADE_EXPLOSION));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateDeathArrow(
	const sf::Vector2f& position, float rotation)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::DEATH_ARROW);
	GameObject* game_object = new GameObject(ObjectClass::DEATH_ARROW, sprite, position);
	game_object->sprite().set_rotation(rotation);
	game_object->Attach(new DieOnCollisionPart(CollisionType::PLAYER));
	game_object->Attach(new DamageOnCollisionPart(CollisionType::PLAYER, 50));
	game_object->Attach(new TimedDeathPart(10));
	game_object->velocity() = VectorMath::Velocity<float>((float)(rotation * M_PI / 180), 15);
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateSplitter(
	const sf::Vector2f& position, float scale, int iteration)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::BLOB);
	sprite.set_scale(sf::Vector2f(scale, scale));
	GameObject* game_object = new GameObject(ObjectClass::SPLITTER, sprite, position, 50);
	game_object->health() = 50;
	game_object->set_coll_type(CollisionType::ENEMY);
	game_object->max_speed() = 8;
	game_object->Attach(new DieOnCollisionPart(CollisionType::PLAYER));
	game_object->Attach(new BouncingPart());
	game_object->Attach(new VelocityRandomizerPart());
	game_object->Attach(new SplitterControllerPart(iteration));
	game_object->Attach(new BoundingPart(CalculateBounds(game_object)));
	std::vector<GameObject*> spawns = std::vector<GameObject*>();
	spawns.push_back(CreateGameObject(ObjectClass::EXPLOSION, sf::Vector2f(0, 0)));
	game_object->Attach(new SpawnOnDiePart(spawns));
	game_object->Attach(new SoundOnDiePart(SoundKey::ARCADE_EXPLOSION));
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateExplosion(
	const sf::Vector2f& position, SpriteKey::Enum sprite_key)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(sprite_key);
	GameObject* game_object = new GameObject(ObjectClass::EXPLOSION, sprite, position);
	game_object->Attach(new DieAfterAnimationPart());
	game_object->sprite().PlayAnimation(false);
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateSpeedPowerUp(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::WINGS);
	GameObject* game_object = new GameObject(ObjectClass::SPEED_POWER_UP, sprite, position);
	game_object->max_speed() = 10;
	game_object->set_coll_type(CollisionType::NONE);
	game_object->Attach(new TimedDeathPart(8));
	game_object->Attach(new AddPartOnCollisionPart(
		new SpeedMultiplierPart(5, 2), ObjectClass::PLAYER));
	game_object->Attach(new VelocityRandomizerPart());
	game_object->Attach(new BouncingPart());
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateFireRatePowerUp(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::BULLETS);
	GameObject* game_object = new GameObject(ObjectClass::FIRE_RATE_POWER_UP, sprite, position);
	game_object->max_speed() = 10;
	game_object->set_coll_type(CollisionType::NONE);
	game_object->Attach(new TimedDeathPart(8));
	game_object->Attach(new AddPartOnCollisionPart(
		new FireRateMultiplierPart(5, 0.5), ObjectClass::PLAYER));
	game_object->Attach(new VelocityRandomizerPart());
	game_object->Attach(new BouncingPart());
	return game_object;
}

gun::GameObject* gun::GameObjectFactory::CreateGhostingPowerUp(const sf::Vector2f& position)
{
	Sprite sprite = Services::Instance().sprite_cache()->GetSprite(SpriteKey::GHOST);
	GameObject* game_object = new GameObject(ObjectClass::GHOSTING_POWER_UP, sprite, position);
	game_object->max_speed() = 10;
	game_object->set_coll_type(CollisionType::NONE);
	game_object->Attach(new TimedDeathPart(8));
	game_object->Attach(new AddPartOnCollisionPart(
		new GhostPart(3), ObjectClass::PLAYER));
	game_object->Attach(new VelocityRandomizerPart());
	game_object->Attach(new BouncingPart());
	return game_object;
}

std::vector<sf::FloatRect> gun::GameObjectFactory::CalculateBounds(
	const GameObject* game_object)
{
	std::vector<sf::FloatRect> bounds = std::vector<sf::FloatRect>();
	sf::FloatRect level_area = Services::Instance().level().area;
	bounds.push_back(level_area);
	bounds.push_back(PolygonMath::Stretch(level_area, game_object->size()));
	return bounds;
}