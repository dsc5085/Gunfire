#ifndef GUN_TEXT_DECORATOR_H
#define GUN_TEXT_DECORATOR_H

namespace gun
{
	class Text;

	class TextDecorator
	{
	public:
		virtual bool is_expired() const { return false; }

		virtual TextDecorator* clone() const = 0;
		virtual void Update(Text& text, double dt) { }
	};

	inline TextDecorator* new_clone(const TextDecorator& other) {
		return other.clone();
	}
}

#endif