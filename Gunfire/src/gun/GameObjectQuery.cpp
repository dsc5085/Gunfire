#include "GameObjectQuery.h"
#include "VectorMath.h"
#include "GameObject.h"
#include "Services.h"
#include "ObjectManager.h"

std::vector<gun::GameObject*> gun::GameObjectQuery::GetByObjectClass(
	ObjectClass::Enum object_class)
{
	std::vector<GameObject*> found_game_objects = std::vector<GameObject*>();

	for(boost::ptr_vector<GameObject>::iterator i
		= Services::Instance().object_manager()->begin(); 
		i != Services::Instance().object_manager()->end(); i++)
	{
		if (i->object_class() == object_class)
		{
			found_game_objects.push_back(&*i);
		}
	}

	return found_game_objects;
}

std::vector<gun::GameObject*> gun::GameObjectQuery::GetByCollisionType(
	CollisionType::Enum coll_type)
{
	std::vector<GameObject*> found_game_objects = std::vector<GameObject*>();

	for(boost::ptr_vector<GameObject>::iterator i
		= Services::Instance().object_manager()->begin(); 
		i != Services::Instance().object_manager()->end(); i++)
	{
		if (i->coll_type() == coll_type)
		{
			found_game_objects.push_back(&*i);
		}
	}

	return found_game_objects;
}

std::vector<gun::GameObject*> gun::GameObjectQuery::GetInRadius(
	const sf::Vector2f& begin, double radius)
{
	std::vector<GameObject*> found_game_objects = std::vector<GameObject*>();

	for(boost::ptr_vector<GameObject>::iterator i
		= Services::Instance().object_manager()->begin(); 
		i != Services::Instance().object_manager()->end(); i++)
	{
		if (VectorMath::Length(i->center() - begin) <= radius)
		{
			found_game_objects.push_back(&*i);
		}
	}

	return found_game_objects;
}

gun::GameObject* gun::GameObjectQuery::GetNearest(const GameObject* searcher, 
	const std::vector<GameObject*>& game_objects)
{
	GameObject* nearest_object = 0;

	if(game_objects.size() > 0)
	{
		nearest_object = game_objects[0];

		for (unsigned int i = 0; i < game_objects.size(); i++)
		{
			if (VectorMath::Length(game_objects[i]->position() - searcher->position())
				< VectorMath::Length(nearest_object->position() - searcher->position()))
			{
				nearest_object = game_objects[i];
			}
		}
	}

	return nearest_object;
}