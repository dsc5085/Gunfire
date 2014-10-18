#ifndef GUN_OBJECT_CLASS_H
#define GUN_OBJECT_CLASS_H

#include "Macros.h"

namespace gun
{
	namespace ObjectClass
	{
		enum Enum
		{
			PLAYER, 
			PLAYER_BULLET, 
			GRUNT, 
			GRUNT_HEAD, 
			GRUNT_ARM, 
			GRUNT_LEG, 
			DRONE, 
			DRONE_BULLET, 
			EXPLODER, 
			SPLITTER, 
			DEATH_ARROW, 
			BLOOD, 
			EXPLOSION, 
			SPEED_POWER_UP, 
			FIRE_RATE_POWER_UP, 
			GHOSTING_POWER_UP, 
			NONE
		};

		const char* StringValue[];
	};
}

#endif