#include "GruntControllerPart.h"
#include "Math.h"
#include "VectorMath.h"
#include "DiedEventArgs.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Services.h"
#include "EventManager.h"
#include "GameObjectQuery.h"

gun::GruntControllerPart::GruntControllerPart()
	: scan_timer_(Timer(50)), target_(0)
{
}

void gun::GruntControllerPart::Initialize()
{
	died_bind_ = Services::Instance().event_manager()->Subscribe<DiedEventArgs>(
		boost::bind(&gun::GruntControllerPart::Handle_Died, this, _1));
}

void gun::GruntControllerPart::Cleanup()
{
	died_bind_.Unsubscribe();
}

void gun::GruntControllerPart::Update(double dt)
{
	scan_timer_.Update(1);
	GameObjectQuery* object_query = Services::Instance().object_query();

	if (scan_timer_.Check())
	{
		std::vector<GameObject*> players
			= object_query->GetByObjectClass(ObjectClass::PLAYER);
		target_ = object_query->GetNearest(game_object_, players);
	}

	if (target_ != 0)
	{
		sf::Vector2f offset = target_->center() - game_object_->center();
		game_object_->velocity() = VectorMath::Lengthen(offset, game_object_->max_speed());
		double angle = VectorMath::Angle(game_object_->velocity());

		if (angle >= M_PI / 4 && angle <= 3 * M_PI / 4)
		{
			game_object_->sprite().PlayAnimation(3, true);
		}
		else if (angle >= 5 * M_PI / 4 && angle <= 7 * M_PI / 4)
		{
			game_object_->sprite().PlayAnimation(0, true);
		}
		else if (angle >= 7 * M_PI / 4 || angle <= M_PI / 4)
		{
			game_object_->sprite().PlayAnimation(2, true);
		}
		else
		{
			game_object_->sprite().PlayAnimation(1, true);
		}
	}
	else
	{
		game_object_->sprite().PauseAnimation();
		game_object_->velocity() = sf::Vector2f(0, 0);
	}
}

void gun::GruntControllerPart::Handle_Died(DiedEventArgs& args)
{
	if (args.game_object == target_)
	{
		// If the target died, set target to null.
		target_ = 0;
	}

	if (game_object_ == args.game_object)
	{
		std::vector<GameObject*> gibs;
		gibs.push_back(GameObjectFactory::CreateGameObject(
			ObjectClass::GRUNT_HEAD, game_object_->position()));
		gibs.push_back(GameObjectFactory::CreateGameObject(
			ObjectClass::GRUNT_ARM, game_object_->position()));
		gibs.push_back(GameObjectFactory::CreateGameObject(
			ObjectClass::GRUNT_ARM, game_object_->position()));
		gibs.push_back(GameObjectFactory::CreateGameObject(
			ObjectClass::GRUNT_LEG, game_object_->position()));
		gibs.push_back(GameObjectFactory::CreateGameObject(
			ObjectClass::GRUNT_LEG, game_object_->position()));

		for (unsigned int i = 0; i < gibs.size(); i++)
		{
			float velocity_x = (float)Math::Random(-5, 5);
			float velocity_y = (float)Math::Random(0, -10);
			gibs[i]->velocity() = sf::Vector2f(velocity_x, velocity_y);
			game_object_->Spawn(gibs[i]);
		}
	}
}