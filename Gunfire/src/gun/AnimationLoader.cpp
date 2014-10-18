#include <boost\algorithm\string.hpp>

#include "AnimationFormat.h"
#include "AnimationLoader.h"
#include "AnimationFactory.h"
#include "PugiUtility.h"

 std::map<int, gun::Animation> gun::AnimationLoader::Load(const std::string& file_name)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file_name.c_str());

	if (result.status != pugi::status_ok)
	{
		std::string message
			= std::string("Could not load '") + file_name + "':  " + result.description();
		throw std::runtime_error(message);
	}

	pugi::xml_node root = doc.child("animations");
	std::map<int, Animation> animations = std::map<int, Animation>();
	int anim_index = 0;

	for (pugi::xml_node_iterator it = root.begin(); it != root.end(); ++it)
	{
		AnimationFormat::Enum format = AnimationFormat::BLOCK;
		std::vector<sf::IntRect> frames = std::vector<sf::IntRect>();
		const pugi::char_t* name = it->child_value("name");
		const pugi::char_t* data = it->child_value("data");
		std::vector<pugi::string_t> data_values = std::vector<pugi::string_t>();
		boost::split(data_values, data, boost::is_any_of(","));

		if (it->child("format") != 0)
		{
			const pugi::char_t* format_char = it->child_value("format");

			if (strcmp(format_char, "LINE") == 0)
			{
				format = AnimationFormat::LINE;
			}
			else
			{
				std::string message = std::string(format_char) + " is not a valid format.";
				throw std::invalid_argument(message);
			}
		}

		switch (format)
		{
		case AnimationFormat::BLOCK:
			animations[anim_index] = GetFramesByBlockFormat(data_values);
			break;
		case AnimationFormat::LINE:
			animations[anim_index] = GetFramesByLineFormat(data_values);
			break;
		default:
			std::string message = format + " is not a supported format.";
			throw std::invalid_argument(message);
		}

		anim_index++;
	}

	return animations;
 }
 
gun::Animation gun::AnimationLoader::GetFramesByBlockFormat(
	std::vector<pugi::string_t> data_values)
{
	std::vector<sf::IntRect> frames = std::vector<sf::IntRect>();

	for (unsigned int i = 0; i < data_values.size() / 4; i++)
	{
		int index = i * 4;
		sf::IntRect frame = sf::IntRect(
			atoi(data_values[index].c_str()), 
			atoi(data_values[index + 1].c_str()), 
			atoi(data_values[index + 2].c_str()), 
			atoi(data_values[index + 3].c_str()));
		frames.push_back(frame);
	}

	return Animation(frames);
}

gun::Animation gun::AnimationLoader::GetFramesByLineFormat(
	std::vector<pugi::string_t> data_values)
{
	Animation animation = AnimationFactory::CreateAnimation(
		atoi(data_values[0].c_str()), 
		atoi(data_values[1].c_str()), 
		atoi(data_values[2].c_str()), 
		atoi(data_values[3].c_str()));

	return animation;
}