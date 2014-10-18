#include "Sprite.h"

void gun::Sprite::set_frame(double frame)
{
	frame_ = frame;

	if(frame_ < current_anim().num_frames())
	{
		sf::IntRect source_rect = current_anim().GetSourceRect(this->frame());
		sprite_.setTextureRect(source_rect);
		sprite_.setOrigin((float)(source_rect.width / 2), (float)(source_rect.height / 2));
	}
}

gun::Sprite::Sprite()
{
}

gun::Sprite::Sprite(const sf::Texture& texture)
	: sprite_(sf::Sprite(texture)), draw_order_(0), is_visible_(true)
{
	sprite_.setOrigin((float)(texture.getSize().x / 2), (float)(texture.getSize().y / 2));
}

gun::Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& rect)
	: sprite_(sf::Sprite(texture, rect)), draw_order_(0), is_visible_(true)
{
	sprite_.setOrigin((float)(rect.width / 2), (float)(rect.height / 2));
}

gun::Sprite::Sprite(const sf::Texture& texture, 
	const Animation& animation, double anim_speed)
	: sprite_(sf::Sprite(texture)), draw_order_(0), is_visible_(true), is_playing_(false), 
	is_looping_(false), anim_speed_(anim_speed), anim_index_(0)
{
	animations_.insert(std::pair<int, Animation>(anim_index_, animation));
	set_frame(0);
}

gun::Sprite::Sprite(const sf::Texture& texture, 
	const std::map<int, Animation>& animations, int anim_index, double anim_speed)
	: sprite_(sf::Sprite(texture)), draw_order_(0), is_visible_(true), is_playing_(false),
	is_looping_(false), animations_(animations), anim_speed_(anim_speed), anim_index_(anim_index)
{
	set_frame(0);
}

void gun::Sprite::PlayAnimation(bool is_looping)
{
	PlayAnimation(anim_index_, is_looping);
}

void gun::Sprite::PlayAnimation(int anim_index, bool is_looping)
{
	int old_anim_index = anim_index_;

	// If not playing an animation or playing a different animation...
	if (!is_playing_ || anim_index != anim_index_)
	{
		// Set playing to true, set if it should loop, and set the animation.
		is_playing_ = true;
		is_looping_ = is_looping;
		anim_index_ = anim_index;
	}

	if (anim_index != old_anim_index)
	{
		set_frame(0);
	}
}

void gun::Sprite::PauseAnimation()
{
	is_playing_ = false;
}

void gun::Sprite::StopAnimation()
{
	is_playing_ = false;
	set_frame(0);
}

void gun::Sprite::Update(double dt)
{
	if(animations_.size() > 0)
	{
		Animation animation = current_anim();

		if (is_playing_)
		{
			if (frame_ >= animation.num_frames())
			{
				if (is_looping_)
				{
					set_frame(0);
				}
				else
				{
					set_frame(animation.num_frames() - 1);
					is_playing_ = false;
				}
			}

			set_frame(frame_ + dt * anim_speed_);
		}
	}
}

void gun::Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(is_visible_)
	{
		target.draw(sprite_, states);
	}
}