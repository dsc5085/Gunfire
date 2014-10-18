#ifndef GUN_SPLITTER_CONTROLLER_PART_H
#define GUN_SPLITTER_CONTROLLER_PART_H

#include "Part.h"
#include "EventBind.h"

namespace gun
{
	class DiedEventArgs;

	class SplitterControllerPart : public Part
	{
	public:
		SplitterControllerPart(int iteration);

		void Initialize();
		void Cleanup();

	private:
		int iteration_;
		int split_num_;
		EventBind died_bind_;

		void Handle_Died(DiedEventArgs& args);
	};
}

#endif