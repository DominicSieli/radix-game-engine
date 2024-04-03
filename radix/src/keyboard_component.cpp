#include "keyboard_component.h"

namespace Radix
{
	KeyboardComponent::KeyboardComponent()
	{}

	KeyboardComponent::KeyboardComponent(std::string up_key, std::string down_key, std::string left_key, std::string right_key, std::string shoot_key)
	{
		this->up_key = SDL_Keycode(up_key);
		this->down_key = SDL_Keycode(down_key);
		this->left_key = SDL_Keycode(left_key);
		this->right_key = SDL_Keycode(right_key);
		this->shoot_key = SDL_Keycode(shoot_key);
	}

	std::string KeyboardComponent::SDL_Keycode(std::string key)
	{
		if(key.compare("up") == 0) return "1073741906";
		if(key.compare("down") == 0) return "1073741905";
		if(key.compare("left") == 0) return "1073741904";
		if(key.compare("right") == 0) return "1073741903";
		if(key.compare("space") == 0) return "32";

		return std::to_string(static_cast<int>(key[0]));
	}

	void KeyboardComponent::Initialize()
	{
		transform_component = entity->GetComponent<TransformComponent>();
		sprite_component = entity->GetComponent<SpriteComponent>();
	}

	void KeyboardComponent::Update(float delta_time)
	{
		if(Game::event.type == SDL_KEYDOWN)
		{
			int speed = 100;
			std::string key_code = std::to_string(Game::event.key.keysym.sym);

			if(key_code.compare(up_key) == 0)
			{
				transform_component->velocity.x = 0;
				transform_component->velocity.y = -speed;
				sprite_component->Play("UpAnimation");
			}

			if(key_code.compare(down_key) == 0)
			{
				transform_component->velocity.x = 0;
				transform_component->velocity.y = speed;
				sprite_component->Play("DownAnimation");
			}

			if(key_code.compare(left_key) == 0)
			{
				transform_component->velocity.x = -speed;
				transform_component->velocity.y = 0;
				sprite_component->Play("LeftAnimation");
			}

			if(key_code.compare(right_key) == 0)
			{
				transform_component->velocity.x = speed;
				transform_component->velocity.y = 0;
				sprite_component->Play("RightAnimation");
			}

			if(key_code.compare(shoot_key) == 0)
			{}
		}

		if(Game::event.type == SDL_KEYUP)
		{
			std::string key_code = std::to_string(Game::event.key.keysym.sym);

			if(key_code.compare(up_key) == 0)
			{
				transform_component->velocity.y = 0;
			}

			if(key_code.compare(down_key) == 0)
			{
				transform_component->velocity.y = 0;
			}

			if(key_code.compare(left_key) == 0)
			{
				transform_component->velocity.x = 0;
			}

			if(key_code.compare(right_key) == 0)
			{
				transform_component->velocity.x = 0;
			}

			if(key_code.compare(shoot_key) == 0)
			{}
		}
	}
}