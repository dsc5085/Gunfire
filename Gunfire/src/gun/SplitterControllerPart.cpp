#include "SplitterControllerPart.h"
#include "DiedEventArgs.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Services.h"
#include "EventManager.h"

gun::SplitterControllerPart::SplitterControllerPart(int iteration)
	: iteration_(iteration), split_num_(2)
{
}

void gun::SplitterControllerPart::Initialize()
{
	died_bind_ = Services::Instance().event_manager()->Subscribe<DiedEventArgs>(
		boost::bind(&gun::SplitterControllerPart::Handle_Died, this, _1));
}

void gun::SplitterControllerPart::Cleanup()
{
	died_bind_.Unsubscribe();
}

void gun::SplitterControllerPart::Handle_Died(DiedEventArgs& args)
{
	if (args.game_object == game_object_)
	{
		if (iteration_ > 0)
		{
			for (int i = 0; i < split_num_; i++)
			{
				GameObject* splitter = GameObjectFactory::CreateSplitter(
					game_object_->position(), game_object_->sprite().scale().x * 0.75f, 
					iteration_ - 1);
				game_object_->Spawn(splitter);
			}
		}
	}
}