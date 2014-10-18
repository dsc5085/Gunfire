#include "GameObject.h"
#include "PolygonMath.h"
#include "DiedEventArgs.h"
#include "Part.h"
#include "Services.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "ViewManager.h"

sf::FloatRect gun::GameObject::coll_box() const
{
	return sf::FloatRect(position_.x, position_.y, 
		sprite_.size().x / 32.f, sprite_.size().y / 32.f);
}

sf::Vector2f gun::GameObject::size() const
{
	sf::FloatRect col_box = coll_box();
	return sf::Vector2f(col_box.width, col_box.height);
}

sf::Vector2f gun::GameObject::center() const
{
	sf::FloatRect col_box = coll_box();
	sf::Vector2f center = PolygonMath::Center(col_box);
	return center;
}

gun::GameObject::GameObject(ObjectClass::Enum object_class, const Sprite& sprite, 
	const sf::Vector2f& position)
{
	Init(object_class, sprite, position, 0);
}

gun::GameObject::GameObject(ObjectClass::Enum object_class, const Sprite& sprite, 
	const sf::Vector2f& position, int points)
{
	Init(object_class, sprite, position, points);
}

void gun::GameObject::Die()
{
	Services::Instance().event_manager()->Publish(DiedEventArgs(this));
	sprite_.set_is_visible(false);
	is_active_ = false;
	Services::Instance().object_manager()->MarkRemoved(this);
}

void gun::GameObject::Update(double dt)
{
	Entity::Update(dt);
	age_ += dt;
	position_ += velocity_ * (float)dt;

	if (health_ <= 0)
	{
		Die();
	}

	sprite_.Update(dt);
	sprite_.set_position(position_ * 32.f + sprite_.origin());
}

void gun::GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(sprite_);
}

std::string gun::GameObject::Details()
{
	return boost::lexical_cast<std::string>(this)
		+ "[" + ObjectClass::StringValue[object_class_] + "]";
}

void gun::GameObject::Spawn(GameObject* spawn)
{
	// Calculates the offset so that spawn is created at the center of the spawner.
	sf::Vector2f offset = center() - spawn->center();
	spawn->position_ += offset;
	Services::Instance().object_manager()->MarkAdded(spawn);
	spawn->Initialize();
}

void gun::GameObject::Init(ObjectClass::Enum object_class, const Sprite& sprite, 
	const sf::Vector2f& position, int points)
{
	is_active_ = true;
	object_class_ = object_class;
	coll_type_ = CollisionType::NONE;
	age_ = 0;
	position_ = position;
	velocity_ = sf::Vector2f(0, 0);
	max_health_ = 1;
	health_ = max_health_;
	max_speed_ = 0;
	points_ = points;
	sprite_ = sprite;
}

void gun::GameObject::SetParent(Part* part)
{
	part->set_game_object(this);
}