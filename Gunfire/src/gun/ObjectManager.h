#ifndef GUN_OBJECT_MANAGER_H
#define GUN_OBJECT_MANAGER_H

#include <vector>
#include <boost\ptr_container\ptr_vector.hpp>

namespace gun
{
	template<typename T>
	class ObjectManager
	{
	public:
		typename boost::ptr_vector<T>::iterator begin() { return objects_.begin(); }
		typename boost::ptr_vector<T>::iterator end() { return objects_.end(); }
		
		void Add(T* object);
		void MarkAdded(T* object);
		void MarkRemoved(T* object);
		void Clear();
		void Update();

	private:
		boost::ptr_vector<T> objects_;
		std::vector<T*> added_;
		std::vector<T*> removed_;
		
		void Remove(T* object);
	};

	template<typename T>
	void ObjectManager<T>::Add(T* object)
	{
		objects_.push_back(object);
	}

	template<typename T>
	void ObjectManager<T>::MarkAdded(T* object)
	{
		added_.push_back(object);
	}

	template<typename T>
	void ObjectManager<T>::MarkRemoved(T* object)
	{
		removed_.push_back(object);
	}

	template<typename T>
	void ObjectManager<T>::Clear()
	{
		objects_.clear();
	}

	template<typename T>
	void ObjectManager<T>::Update()
	{
		while(!added_.empty())
		{
			objects_.push_back(added_.back());
			added_.pop_back();
		}

		while(!removed_.empty())
		{
			Remove(removed_.back());
			removed_.pop_back();
		}
	}

	template<typename T>
	void ObjectManager<T>::Remove(T* object)
	{
		for(boost::ptr_vector<T>::iterator i = objects_.begin(); 
			i != objects_.end(); i++)
		{
			if(&*i == object)
			{
				objects_.erase(i);
				break;
			}
		}
	}
}

#endif