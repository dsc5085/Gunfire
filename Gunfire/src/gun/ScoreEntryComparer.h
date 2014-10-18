#ifndef GUN_SCORE_ENTRY_COMPARER_H
#define GUN_SCORE_ENTRY_COMPARER_H

#include "ScoreEntry.h"

namespace gun
{
	struct ScoreEntryComparer
	{
		bool operator() (ScoreEntry score_entry1, ScoreEntry score_entry2)
		{ 
			return score_entry1.score > score_entry2.score;
		}
	};
}

#endif