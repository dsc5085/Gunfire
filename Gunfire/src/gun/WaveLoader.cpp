#include "WaveLoader.h"
#include "PugiUtility.h"
#include "FileIO.h"

std::vector<gun::Wave> gun::WaveLoader::LoadWaves(const std::string& file_name)
{
	std::vector<std::string> lines = FileIO::LoadLines(file_name);
	std::vector<Wave> waves = std::vector<Wave>();

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		Wave wave = LoadWave(lines[i].c_str());
		waves.push_back(wave);
	}

	return waves;
}

gun::Wave gun::WaveLoader::LoadWave(const std::string& file_name)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file_name.c_str());

	if (result.status != pugi::status_ok)
	{
		std::string message
			= std::string("Could not load '") + file_name + "':  " + result.description();
		throw std::runtime_error(message);
	}

	pugi::xml_node root = doc.child("wavepoints");
	// pugi::xml_node root = PugiUtility::LoadRoot(file_name, "wavepoints");
	Wave wave = Wave();
	
	for (pugi::xml_node_iterator it = root.begin(); it != root.end(); ++it)
	{
		WavePoint wave_point = WavePoint();
		wave_point.duration = atoi(it->child_value("duration"));
		pugi::xml_node objects_node = it->child("objects");
		
		for (pugi::xml_node it2 = objects_node.child("object");
			it2; it2 = it2.next_sibling("object"))
		{
			const pugi::char_t* class_index = it2.child_value("class");
			int number = atoi(it2.child_value("number"));
			wave_point.objects[class_index] = number;
		}

		wave.wave_points.push_back(wave_point);
	}

	return wave;
}