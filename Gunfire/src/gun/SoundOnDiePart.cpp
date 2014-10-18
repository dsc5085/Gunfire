#include "SoundOnDiePart.h"
#include "DiedEventArgs.h"
#include "Services.h"
#include "EventManager.h"
#include "SoundCache.h"

gun::SoundOnDiePart::SoundOnDiePart(SoundKey::Enum sound_key)
	: sound_key_(sound_key)
{
}

void gun::SoundOnDiePart::Initialize()
{
	died_bind_ = Services::Instance().event_manager()->Subscribe<DiedEventArgs>(
		boost::bind(&gun::SoundOnDiePart::Handle_Died, this, _1));
}

void gun::SoundOnDiePart::Cleanup()
{
	died_bind_.Unsubscribe();
}

void gun::SoundOnDiePart::Handle_Died(DiedEventArgs& args)
{
	if (game_object_ == args.game_object)
	{
		Services::Instance().sound_cache()->PlaySound(sound_key_);
	}
}