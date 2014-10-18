#ifndef GUN_ANIMATION_FACTORY_H
#define GUN_ANIMATION_FACTORY_H

#include "Animation.h"

namespace gun
{
	class AnimationFactory
	{
	public:
		static Animation CreateAnimation(int sheet_width, 
			int sprite_width,int sprite_height, int frames);
	};
}

#endif