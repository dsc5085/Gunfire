#include "PlayerControllerPart.h"
#include "VectorMath.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Services.h"
#include "SoundCache.h"

gun::PlayerControllerPart::PlayerControllerPart()
	: bullet_speed_(25), reload_timer_(Timer(0.2))
{
}

void gun::PlayerControllerPart::Initialize()
{
	input_map_ = Services::Instance().session().input_map;
}

void gun::PlayerControllerPart::Update(double dt)
{
	reload_timer_.Update(dt);
	sf::Vector2f velocity(0, 0);
	sf::Vector2f bullet_velocity(0, 0);

	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::MOVE_UP]))
	{
		velocity.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::MOVE_DOWN]))
	{
		velocity.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::MOVE_LEFT]))
	{
		velocity.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::MOVE_RIGHT]))
	{
		velocity.x += 1;
	}

	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::FIRE_UP]))
	{
		bullet_velocity.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::FIRE_DOWN]))
	{
		bullet_velocity.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::FIRE_LEFT]))
	{
		bullet_velocity.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(input_map_[InputAction::FIRE_RIGHT]))
	{
		bullet_velocity.x += 1;
	}

	if(velocity.x != 0 || velocity.y != 0)
	{
		int anim_index;
		
		if (velocity.y > 0)
		{
			anim_index = 1;
		}
		else if (velocity.y < 0)
		{
			anim_index = 0;
		}
		if (velocity.x > 0)
		{
			anim_index = 3;
		}
		else if (velocity.x < 0)
		{
			anim_index = 2;
		}

		velocity = VectorMath::Lengthen(velocity, game_object_->max_speed());
		game_object_->sprite().PlayAnimation(anim_index, true);
	}
	else
	{
		game_object_->sprite().PauseAnimation();
	}
	
	game_object_->velocity() = velocity;

	if(bullet_velocity.x != 0 || bullet_velocity.y != 0)
	{
		if(reload_timer_.Check())
		{
			bullet_velocity = VectorMath::Lengthen(bullet_velocity, bullet_speed_);
			GameObject* bullet = GameObjectFactory::CreateGameObject(
				ObjectClass::PLAYER_BULLET, game_object_->position());
			bullet->velocity() = bullet_velocity;
			game_object_->Spawn(bullet);
			Services::Instance().sound_cache()->PlaySound(SoundKey::GUN_SHOT);
		}
	}
}