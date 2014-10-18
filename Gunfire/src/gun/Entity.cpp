#include <boost\lexical_cast.hpp>

#include "Entity.h"
#include "Part.h"

gun::Entity::Entity()
	: is_initialized_(false)
{
}

gun::Entity::~Entity()
{
	for(boost::ptr_map<int, Part>::iterator it = parts_.begin(); it != parts_.end(); it++)
	{
		it->second->Cleanup();
	}
}

void gun::Entity::Attach(Part* part)
{
	int key = typeid(*part).hash_code();

	if (parts_.find(key) == parts_.end())
	{
		parts_.insert(key, part);
		SetParent(part);

		if (is_initialized_)
		{
			part->Initialize();
		}
	}
	else
	{
		std::string message = std::string(typeid(Entity).name()) +
			": Attach failed.  Part of type " + typeid(*part).name() + 
			" could not be added because a Part of the same type already exists.";
		throw std::invalid_argument(message);
	}
}

void gun::Entity::Replace(Part* part)
{
	int key = typeid(*part).hash_code();

	if (parts_.find(key) != parts_.end())
	{
		Detach(key);
	}

	if (is_initialized_)
	{
		parts_to_add_.push_back(part);
	}
	else
	{
		Attach(part);
	}
}

void gun::Entity::Detach(int key)
{
	parts_to_remove_.push_back(key);
}

void gun::Entity::RemovePart(int key)
{
	if (parts_.find(key) != parts_.end())
	{
		Part* removed_part = parts_.find(key)->second;
		removed_part->Cleanup();
		parts_.erase(key);
	}
	else
	{
		std::string message = "Entity: Detach failed.  Part with key id "
			+ boost::lexical_cast<std::string>(key) + " could not be found.";
		throw std::invalid_argument(message);
	}
}

void gun::Entity::Initialize()
{
	is_initialized_ = true;

	for(boost::ptr_map<int, Part>::iterator it = parts_.begin(); it != parts_.end(); it++)
	{
		it->second->Initialize();
	}
}

void gun::Entity::Update(double dt)
{
	for (boost::ptr_map<int, Part>::iterator it = parts_.begin(); it != parts_.end(); it++)
	{
		if (it->second->is_active())
		{
			it->second->Update(dt);
		}
	}

	while(!parts_to_remove_.empty())
	{
		RemovePart(parts_to_remove_.back());
		parts_to_remove_.pop_back();
	}

	while(!parts_to_add_.empty())
	{
		Attach(parts_to_add_.back());
		parts_to_add_.pop_back();
	}
}