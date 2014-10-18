#ifndef GUN_TEXT_FADE_DECORATOR_H
#define GUN_TEXT_FADE_DECORATOR_H

#include "TextDecorator.h"

namespace gun
{
	class TextFadeDecorator : public TextDecorator
	{
	public:
		bool is_expired() const { return !is_looping_ && age_ >= max_age_; }

		TextFadeDecorator(double max_age);
		TextFadeDecorator(double max_age, bool is_looping);

		TextFadeDecorator* clone() const { return new TextFadeDecorator(*this); }
		void Update(Text& text, double dt);

	private:
		enum FadeState
		{
			FADE, 
			DEFADE
		};

		bool is_looping_;
		FadeState fade_state_;
		double age_;
		double max_age_;
	};
}

#endif