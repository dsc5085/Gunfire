#ifndef GUN_SPRITE_H
#define GUN_SPRITE_H

#include <SFML\Graphics.hpp>

#include "Animation.h"

namespace gun
{
	class Sprite : public sf::Drawable
	{
	public:
		bool is_visible() const { return is_visible_; }
		sf::Vector2f origin() const { return sprite_.getOrigin(); }
		sf::Vector2f scale() const { return sprite_.getScale(); }
		sf::Vector2f position() const { return sprite_.getPosition(); }
		float rotation() const { return sprite_.getRotation(); }

		sf::Vector2i size() const
		{
			return sf::Vector2i((int)sprite_.getGlobalBounds().width, 
				(int)sprite_.getGlobalBounds().height);
		}
		
		sf::Color color() const { return sprite_.getColor(); }
		double draw_order() const { return draw_order_; }
		bool is_playing() const { return is_playing_; }
		Animation current_anim() const { return animations_.at(anim_index_); }
		int frame() const { return (int)floor(frame_); }

		void set_is_visible(bool is_visible) { is_visible_ = is_visible; }
		void set_color(const sf::Color& color) { sprite_.setColor(color); }
		void set_origin(const sf::Vector2f& origin) { sprite_.setOrigin(origin); }
		void set_scale(const sf::Vector2f& scale) { sprite_.setScale(scale); }
		void set_position(const sf::Vector2f& position) { sprite_.setPosition(position); }
		void set_rotation(float rotation) { sprite_.setRotation(rotation); }
		void set_frame(double frame);

		Sprite();
		Sprite(const sf::Texture& texture);
		Sprite(const sf::Texture& texture, const sf::IntRect& rect);
		Sprite(const sf::Texture& texture, const Animation& animation, double anim_speed);
		Sprite(const sf::Texture& texture, const std::map<int, Animation>& animations, 
			int anim_index, double anim_speed);
		
		void PlayAnimation(bool is_looping);
		void PlayAnimation(int anim_index, bool is_looping);
		void PauseAnimation();
		void StopAnimation();
		void Update(double dt);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite sprite_;
		double draw_order_;
		bool is_visible_;
		bool is_playing_;
		bool is_looping_;
		std::map<int, Animation> animations_;
		double anim_speed_;
		int anim_index_;
		double frame_;
	};
}

#endif