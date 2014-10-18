#ifndef GUN_SOUND_ON_DIE_PART_H
#define GUN_SOUND_ON_DIE_PART_H

#include "Part.h"
#include "SoundKey.h"
#include "EventBind.h"

namespace gun
{
	class DiedEventArgs;

	class SoundOnDiePart : public Part
	{
	public:
		SoundOnDiePart(SoundKey::Enum sound_key);

		void Initialize();
		void Cleanup();

	private:
		SoundKey::Enum sound_key_;
		EventBind died_bind_;

		void Handle_Died(DiedEventArgs& args);
	};
}

#endif