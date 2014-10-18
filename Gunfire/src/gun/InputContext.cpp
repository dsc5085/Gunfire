#include <boost/lexical_cast.hpp>

#include "InputContext.h"

gun::InputContext::InputContext(const std::vector<sf::Event>& current_events)
	: current_events_(current_events)
{
}

bool gun::InputContext::CheckForEvent(const sf::Event::EventType& event_type) const
{
	for (unsigned int i = 0; i < current_events_.size(); i++)
	{
		if (current_events_[i].type == event_type)
		{
			return true;
		}
	}

	return false;
}

bool gun::InputContext::IsKeyReleased(const sf::Keyboard::Key& key) const
{
	for (unsigned int i = 0; i < current_events_.size(); i++)
	{
		if (current_events_[i].type == sf::Event::KeyReleased)
		{
			if (current_events_[i].key.code == key)
			{
				return true;
			}
		}
	}

	return false;
}

sf::Event gun::InputContext::GetEvent(const sf::Event::EventType& event_type) const
{
	for (unsigned int i = 0; i < current_events_.size(); i++)
	{
		if (current_events_[i].type == event_type)
		{
			return current_events_[i];
		}
	}

	std::string message = std::string(typeid(InputContext).name()) +
		": GetEvent failed.  Event with event type of "
		+ boost::lexical_cast<std::string>(event_type) + " did not occur.";
	throw std::invalid_argument(message);
}

sf::Uint32 gun::InputContext::GetTextEnteredUnicode() const
{
	int unicode = -1;

	for (unsigned int i = 0; i < current_events_.size(); i++)
	{
		if (current_events_[i].type == sf::Event::TextEntered)
		{
			unicode = current_events_[i].text.unicode;
			break;
		}
	}

	return unicode;
}