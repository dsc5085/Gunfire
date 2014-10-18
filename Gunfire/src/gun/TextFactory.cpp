#include "TextFactory.h"
#include "Paths.h"

void gun::TextFactory::Initialize()
{
	font_.loadFromFile(Paths::FONTS_DIR + "G7 Elevator Action.TTF");
}

gun::Text gun::TextFactory::CreateText(unsigned int size)
{
	return CreateText(size, sf::Vector2f(0, 0));
}

gun::Text gun::TextFactory::CreateText(unsigned int size, const std::string& string)
{
	return CreateText(size, sf::Vector2f(0, 0), string);
}

gun::Text gun::TextFactory::CreateText(unsigned int size, sf::Vector2f position)
{
	return CreateText(size, position, "");
}

gun::Text gun::TextFactory::CreateText(
	unsigned int size, sf::Vector2f position, const std::string& string)
{
	sf::Text text = sf::Text();
	text.setFont(font_);
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setString(string);
	return Text(text);
}