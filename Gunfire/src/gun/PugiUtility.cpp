#include "PugiUtility.h"

pugi::xml_node gun::PugiUtility::LoadRoot(
	const char* file_name, const char* root_name)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file_name);

	if (result.status != pugi::status_ok)
	{
		std::string message
			= std::string("Could not load '") + file_name + "':  " + result.description();
		throw std::runtime_error(message);
	}

	return doc.child(root_name);
}