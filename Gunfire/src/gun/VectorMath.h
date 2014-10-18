#ifndef GUN_VECTOR_MATH_H
#define GUN_VECTOR_MATH_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <SFML\Graphics.hpp>

namespace gun
{
	class VectorMath
	{
	public:
		template<class T>
		static double Length(const sf::Vector2<T>& vector);

		template<class T>
		static sf::Vector2<T> Unit(const sf::Vector2<T>& vector);

		template<class T>
		static sf::Vector2<T> Lengthen(const sf::Vector2<T>& vector, T length);

		template<class T>
		static sf::Vector2<T> Floor(const sf::Vector2<T>& vector);
		
		template<class T>
		static double Angle(const sf::Vector2<T>& vector);
		
		// Gets the angle from one point to another point from the x-axis.
		template<class T>
		static double AngleToPoint(
			const sf::Vector2<T>& from, const sf::Vector2<T>& to);

		template<class T>
		static sf::Vector2<T> Velocity(T angle, T speed);
	};

	template<class T>
	static double VectorMath::Length(const sf::Vector2<T>& vector)
	{
		double length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
		return length;
	}

	template<class T>
	static sf::Vector2<T> VectorMath::Unit(const sf::Vector2<T>& vector)
	{
		double length = Length(vector);
		if(length == 0)
		{
			throw new std::range_error("Cannot calculate unit of vector with length 0.");
		}
		sf::Vector2<T> unit = sf::Vector2<T>(
			vector.x / (float)length, vector.y / (float)length);
		return unit;
	}

	template<class T>
	static sf::Vector2<T> VectorMath::Lengthen(const sf::Vector2<T>& vector, T length)
	{
		sf::Vector2<T> new_vector = Unit(vector);
		return new_vector * length;
	}

	template<class T>
	static sf::Vector2<T> VectorMath::Floor(const sf::Vector2<T>& vector)
	{
		sf::Vector2<T> floor_vector(floor(vector.x), floor(vector.y));
		return floor_vector;
	}
		
	template<class T>
	static double VectorMath::Angle(const sf::Vector2<T>& vector)
	{
		double angle = -atan2(vector.y, vector.x);

		if (angle < 0)
		{
			angle += 2 * M_PI;
		}

		return angle;
	}
	
	template<class T>
	static double VectorMath::AngleToPoint(const sf::Vector2<T>& from, 
		const sf::Vector2<T>& to)
	{
		sf::Vector2f diff = to - from;
		double angle = atan2(diff.y, diff.x);
		return angle;
	}
	
	template<class T>
	static sf::Vector2<T> VectorMath::Velocity(T angle, T speed)
	{
		sf::Vector2f velocity = sf::Vector2f(
			speed * cos(angle), speed * sin(angle));
		return velocity;
	}
}

#endif