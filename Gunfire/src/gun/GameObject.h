#ifndef GUN_GAME_OBJECT_H
#define GUN_GAME_OBJECT_H

#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ObjectClass.h"
#include "CollisionType.h"
#include "Sprite.h"

namespace gun
{
	class CollisionHandler;
	class Part;

	class GameObject : public Entity
	{
	public:
		bool is_active() const { return is_active_; }
		ObjectClass::Enum object_class() const { return object_class_; }
		CollisionType::Enum coll_type() const { return coll_type_; }
		double age() const { return age_; }
		sf::Vector2f position() const { return position_; }
		sf::Vector2f& position() { return position_; }
		sf::Vector2f& velocity() { return velocity_; }
		float& max_health() { return max_health_; }
		float& health() { return health_; }
		float& max_speed() { return max_speed_; }
		int points() const { return points_; }
		sf::FloatRect coll_box() const;
		sf::Vector2f size() const;
		sf::Vector2f center() const;
		Sprite& sprite() { return sprite_; }

		void set_object_class(ObjectClass::Enum object_class) { object_class_ = object_class; }
		void set_coll_type(CollisionType::Enum coll_type) { coll_type_ = coll_type; }
		void set_points(int points) { points_ = points; }

		GameObject(ObjectClass::Enum object_class, const Sprite& sprite, 
			const sf::Vector2f& position);
		GameObject(ObjectClass::Enum object_class, const Sprite& sprite, 
			const sf::Vector2f& position, int points);

		void Spawn(GameObject* spawn);
		void Die();
		void Handle_Collision(GameObject* game_object);
		void Update(double dt);
		void Draw(sf::RenderWindow& window);
		std::string Details();

	private:
		bool is_active_;
		ObjectClass::Enum object_class_;
		CollisionType::Enum coll_type_;
		double age_;
		sf::Vector2f position_;
		sf::Vector2f velocity_;
		float max_health_;
		float health_;
		float max_speed_;
		int points_;
		Sprite sprite_;

		void Init(ObjectClass::Enum object_class, const Sprite& sprite, 
			const sf::Vector2f& position, int points);
		void SetParent(Part* part);
	};
}

#endif