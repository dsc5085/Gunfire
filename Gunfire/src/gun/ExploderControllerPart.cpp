#include <SFML\Graphics.hpp>

#include "ExploderControllerPart.h"
#include "Math.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

gun::ExploderControllerPart::ExploderControllerPart(
	double min_explode_time, double max_explode_time)
{
	double explode_time = Math::Random(min_explode_time, max_explode_time);
	explode_timer_ = Timer(explode_time, 0);
}

void gun::ExploderControllerPart::Update(double dt)
{
	double percentage = explode_timer_.current_time() / explode_timer_.max_time();
	int tint = (int)(255 * (1 - percentage));
	sf::Color color(255, tint, tint);
	game_object_->sprite().set_color(color);

	if (explode_timer_.Check())
	{
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 0));
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 45));
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 90));
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 135));
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 180));
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 225));
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 270));
		game_object_->Spawn(GameObjectFactory::CreateDeathArrow(sf::Vector2f(0, 0), 315));
		game_object_->set_points(0);
		game_object_->Die();
	}

	explode_timer_.Update(dt);
}