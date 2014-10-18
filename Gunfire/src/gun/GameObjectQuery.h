#ifndef GUN_GAME_OBJECT_QUERY_H
#define GUN_GAME_OBJECT_QUERY_H

#include <vector>
#include <SFML\Graphics.hpp>

#include "ObjectClass.h"
#include "CollisionType.h"

namespace gun
{
	class GameObject;

	class GameObjectQuery
	{
	public:
		std::vector<GameObject*> GetByObjectClass(ObjectClass::Enum object_class);
		std::vector<GameObject*> GetByCollisionType(CollisionType::Enum coll_type);
		std::vector<GameObject*> GetInRadius(const sf::Vector2f& begin, double radius);
		GameObject* GetNearest(const GameObject* searcher, 
			const std::vector<GameObject*>& game_objects);
	};
}

#endif