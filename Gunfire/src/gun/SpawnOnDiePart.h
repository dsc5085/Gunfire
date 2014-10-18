#ifndef GUN_SPAWN_ON_DIE_PART_H
#define GUN_SPAWN_ON_DIE_PART_H

#include "Part.h"
#include "ObjectClass.h"
#include "EventBind.h"

namespace gun
{
	class DiedEventArgs;

	class SpawnOnDiePart : public Part
	{
	public:
		SpawnOnDiePart(const std::vector<GameObject*> spawns);

		void Initialize();
		void Cleanup();

	private:
		std::vector<GameObject*> spawns_;
		EventBind died_bind_;

		void Handle_Died(DiedEventArgs& args);
	};
}

#endif