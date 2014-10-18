#ifndef GUN_ENTITY_H
#define GUN_ENTITY_H

#include <string>
#include <vector>
#include <boost\concept_check.hpp>
#include <boost\ptr_container\ptr_map.hpp>

#include "ContainerUtility.h"
#include "Part.h"

namespace gun
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		template<class T>
		bool HasPart() const;

		template<class T>
		T* GetPart();

		void Attach(Part* part);
		void Replace(Part* part);

		template<class T>
		void Detach();

		void Initialize();
		virtual void Update(double dt);

	private:
		bool is_initialized_;
		boost::ptr_map<int, Part> parts_;
		std::vector<Part*> parts_to_add_;
		std::vector<int> parts_to_remove_;

		virtual void SetParent(Part* part) { }
		void Detach(int key);
		void RemovePart(int key);
	};

	template<class T>
	bool Entity::HasPart() const
	{
		BOOST_CONCEPT_ASSERT((boost::Convertible<T, Part>));
		
		int key = typeid(T).hash_code();
		bool has_part = parts_.find(key) != parts_.end();

		return has_part;
	}

	template<class T>
	T* Entity::GetPart()
	{
		BOOST_CONCEPT_ASSERT((boost::Convertible<T, Part>));

		T* part = 0;

		if(HasPart<T>())
		{
			int key = typeid(T).hash_code();
			part = static_cast<T*>(parts_.find(key)->second);
		}
		else
		{
			std::string message = std::string(typeid(GameObject).name()) +
				": GetPart failed.  Part of type " + typeid(T).name() + 
				" could not be found.";
			throw std::invalid_argument(message);
		}

		return part;
	}

	template<class T>
	void Entity::Detach()
	{
		if (HasPart<T>())
		{
			int key = typeid(T).hash_code();
			if (!ContainerUtility::Exists(parts_to_remove_, key))
			{
				Detach(key);
			}
		}
	}
}

#endif