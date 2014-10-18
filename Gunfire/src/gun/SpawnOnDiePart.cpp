#include "SpawnOnDiePart.h"
#include "DiedEventArgs.h"
#include "GameObject.h"
#include "Services.h"
#include "EventManager.h"

gun::SpawnOnDiePart::SpawnOnDiePart(const std::vector<GameObject*> spawns)
	: spawns_(spawns)
{
}

void gun::SpawnOnDiePart::Initialize()
{
	died_bind_ = Services::Instance().event_manager()->Subscribe<DiedEventArgs>(
		boost::bind(&gun::SpawnOnDiePart::Handle_Died, this, _1));
}

void gun::SpawnOnDiePart::Cleanup()
{
	died_bind_.Unsubscribe();
}

void gun::SpawnOnDiePart::Handle_Died(DiedEventArgs& args)
{
	if (game_object_ == args.game_object)
	{
		for (unsigned int i = 0; i < spawns_.size(); i++)
		{
			game_object_->Spawn(spawns_[i]);
		}
	}
}