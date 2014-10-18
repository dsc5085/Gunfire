#ifndef GUN_CONTAINER_UTILITY_H
#define GUN_CONTAINER_UTILITY_H

#include <algorithm>
#include <vector>
#include <boost\ptr_container\ptr_vector.hpp>

namespace gun
{
	class ContainerUtility
	{
	public:
		template<class T>
		static bool Exists(const std::vector<T> &vector, T element);

		template<class T>
		static bool Exists(const boost::ptr_vector<T> &vector, T* element);

		template<class T>
		static void AppendElements(const std::vector<T> &append_from, 
			std::vector<T> &append_to);

		template<class T>
		static void RemoveElement(std::vector<T> &vector, T element);

		template<class T>
		static void RemoveElement(boost::ptr_vector<T> &vector, T* element);

		template<class T>
		static void RemoveElements(std::vector<T> &vector, 
			const std::vector<T> &removed);

		template<class T>
		static void RemoveElements(boost::ptr_vector<T> &vector, 
			const boost::ptr_vector<T> &removed);
	};

	template<class T>
	static bool ContainerUtility::Exists(const std::vector<T> &vector, T element)
	{
		return std::find(vector.begin(), vector.end(), element) !=vector.end();
	}

	template<class T>
	static bool ContainerUtility::Exists(const boost::ptr_vector<T> &vector, T* element)
	{
		bool exists = false;

		for(boost::ptr_vector<T>::const_iterator i = vector.begin(); 
			i != vector.end(); i++)
		{
			if (&*i == element)
			{
				exists = true;
				break;
			}
		}

		return exists;
	}

	template<class T>
	static void ContainerUtility::AppendElements(const std::vector<T> &append_from, 
		std::vector<T> &append_to)
	{
		append_to.insert(append_to.end(), append_from.begin(), append_from.end());
	}

	template<class T>
	static void ContainerUtility::RemoveElement(std::vector<T> &vector, T element)
	{
		for (unsigned int i = 0; i < vector.size(); i++)
		{
			if(vector[i] == element)
			{
				vector.erase(vector.begin() + i);
			}
		}
	}

	template<class T>
	static void ContainerUtility::RemoveElement(boost::ptr_vector<T> &vector, T* element)
	{
		for(boost::ptr_vector<T>::iterator i = vector.begin(); 
			i != vector.end(); i++)
		{
			if (&*i == element)
			{
				vector.erase(i);
				break;
			}
		}
	}

	template<class T>
	static void ContainerUtility::RemoveElements(std::vector<T> &vector, 
		const std::vector<T> &removed)
	{
		for(unsigned int i = 0; i < removed.size(); i++)
		{
			RemoveElement(vector, removed[i]);
		}
	}
}

#endif