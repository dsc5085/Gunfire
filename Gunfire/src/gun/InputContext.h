#ifndef GUN_INPUT_CONTEXT_H
#define GUN_INPUT_CONTEXT_H

#include <SFML\Graphics.hpp>

namespace gun
{
	class InputContext
	{
	public:
		InputContext(const std::vector<sf::Event>& current_events);

		bool CheckForEvent(const sf::Event::EventType& event_type) const;
		bool IsKeyReleased(const sf::Keyboard::Key& key) const;
		sf::Event GetEvent(const sf::Event::EventType& event_type) const;
		sf::Uint32 GetTextEnteredUnicode() const;

	private:
		std::vector<sf::Event> current_events_;
	};
}

#endif