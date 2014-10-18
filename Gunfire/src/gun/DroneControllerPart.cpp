#include "DroneControllerPart.h"
#include "Math.h"
#include "VectorMath.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Services.h"
#include "SoundCache.h"
#include "GameObjectQuery.h"

gun::DroneControllerPart::DroneControllerPart()
	: bullet_speed_(7), max_reload_time_(2), move_timer_(Timer(1))
{
	Reload();
}

void gun::DroneControllerPart::Update(double dt)
{
	move_timer_.Update(dt);
	reload_timer_.Update(dt);
	GameObjectQuery* object_query = Services::Instance().object_query();

	if (move_timer_.Check())
	{
		int random = rand() % 4;

		if (random == 0)
		{
			game_object_->velocity() = sf::Vector2f(0, 0);
		}
		else if (random == 1)
		{
			std::vector<GameObject*> players
				= object_query->GetByObjectClass(ObjectClass::PLAYER);
			GameObject* target = object_query->GetNearest(game_object_, players);
			
			if (target != 0)
			{
				game_object_->velocity() = target->position() - game_object_->center();
				game_object_->velocity() = VectorMath::Lengthen(
					game_object_->velocity(), game_object_->max_speed());
			}
		}
		else
		{
			double angle = Math::Random(0, 2 * M_PI);
			game_object_->velocity() = VectorMath::Velocity(
				(float)angle, game_object_->max_speed());
		}
	}

	if (reload_timer_.Check())
	{
		std::vector<GameObject*> players
			= object_query->GetByObjectClass(ObjectClass::PLAYER);
		GameObject* target = object_query->GetNearest(game_object_, players);

		if (target != 0)
		{
			sf::Vector2f velocity = target->position() - game_object_->center();
			velocity = VectorMath::Lengthen(velocity, bullet_speed_);
			GameObject* bullet = GameObjectFactory::CreateGameObject(
				ObjectClass::DRONE_BULLET, game_object_->position());
			bullet->velocity() = velocity;
			game_object_->Spawn(bullet);
			Services::Instance().sound_cache()->PlaySound(SoundKey::LASER);
		}

		Reload();
	}
}

void gun::DroneControllerPart::Reload()
{
	double reload_time = Math::Random(max_reload_time_, max_reload_time_ * 2);
	reload_timer_.set_max_time(reload_time);
}