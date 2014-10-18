#ifndef GUN_GRUNT_CONTROLLER_PART_H
#define GUN_GRUNT_CONTROLLER_PART_H

#include "Part.h"
#include "Timer.h"
#include "EventBind.h"

namespace gun
{
	class DiedEventArgs;
	class GameObject;

	class GruntControllerPart : public Part
	{
	public:
		GruntControllerPart();

		void Initialize();
		void Cleanup();
		void Update(double dt);

	private:
		EventBind died_bind_;
		Timer scan_timer_;
		GameObject* target_;

		void Handle_Died(DiedEventArgs& args);
	};
}

#endif