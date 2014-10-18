#ifndef GUN_TEXT_H
#define GUN_TEXT_H

#include <boost\ptr_container\ptr_vector.hpp>
#include <SFML\Graphics.hpp>

#include "TextDecorator.h"

namespace gun
{
	class Text
	{
	public:
		sf::Text& sf_text() { return sf_text_; }
		int char_size() const { return sf_text_.getCharacterSize(); }
		sf::FloatRect bounds() const { return sf_text_.getGlobalBounds(); }
		sf::Vector2f position() const { return sf_text_.getPosition(); }
		std::string string() const { return sf_text_.getString(); }
		bool is_expired() const;

		void set_position(const sf::Vector2f& position) { sf_text_.setPosition(position); }
		void set_string(const std::string& string) { sf_text_.setString(string); }
		void set_center(const sf::Vector2f position);
		
		Text();
		Text(sf::Text sf_text);

		void AddDecorator(TextDecorator* decorator);

		template<class T>
		void RemoveDecorators();

		void Update(double dt);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Text sf_text_;
		boost::ptr_vector<TextDecorator> decorators_;
	};

	template<class T>
	void Text::RemoveDecorators()
	{
		for (unsigned int i = 0; i < decorators_.size(); i++)
		{
			if (typeid(decorators_[i]).hash_code() == typeid(T).hash_code())
			{
				decorators_.erase(decorators_.begin() + i);
				i--;
			}
		}
	}
}

#endif