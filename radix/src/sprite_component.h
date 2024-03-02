#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "./animation.h"
#include "./asset_manager.h"
#include "./texture_manager.h"
#include "./transform_component.h"

namespace Radix
{
	class SpriteComponent: public Component
	{
	private:
		SDL_Texture* texture;
		SDL_Rect source;
		SDL_Rect destination;
		TransformComponent* transformComponent;
		bool animated;
		int frames;
		int speed;
		bool fixed;
		unsigned int index = 0;
		std::map<std::string, Animation> animations;
		std::string animationName;
	public:
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

		SpriteComponent(const char* filePath)
		{
			this->animated = false;
			this->fixed = false;
			SetTexture(filePath);
		}

		SpriteComponent(std::string id, unsigned int frames, unsigned int speed, bool directional, bool fixed)
		{
			this->animated = true;
			this->frames = frames;
			this->speed = speed;
			this->fixed = fixed;

			if(directional == true)
			{
				Animation up = Animation(3, frames, speed);
				Animation down = Animation(0, frames, speed);
				Animation left = Animation(2, frames, speed);
				Animation right = Animation(1, frames, speed);

				animations.emplace("UpAnimation", up);
				animations.emplace("DownAnimation", down);
				animations.emplace("LeftAnimation", left);
				animations.emplace("RightAnimation", right);

				this->index = 0;
				this->animationName = "DownAnimation";
			}
			else
			{
				Animation singleAnimation = Animation(0, frames, speed);
				animations.emplace("SingleAnimation", singleAnimation);
				this->index = 0;
				this->animationName = "SingleAnimation";
			}

			Play(this->animationName);
			SetTexture(id);
		}

		void Play(std::string animationName)
		{
			frames = animations[animationName].frames;
			index = animations[animationName].index;
			speed = animations[animationName].speed;
			this->animationName = animationName;
		}

		void SetTexture(std::string assetTextureId)
		{
			texture = Game::assetManager->GetTexture(assetTextureId);
		}

		void Initialize() override
		{
			transformComponent = entity->GetComponent<TransformComponent>();
			source.x = 0;
			source.y = 0;
			source.w = transformComponent->dimension.x;
			source.h = transformComponent->dimension.y;
		}

		void Update(float deltaTime) override
		{
			if(animated == true)
			{
				source.x = source.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
			}

			source.y = index * static_cast<int>(transformComponent->dimension.y);

			destination.x = static_cast<int>(transformComponent->position.x) - ((fixed == true) ? 0 : Game::camera.x);
			destination.y = static_cast<int>(transformComponent->position.y) - ((fixed == true) ? 0 : Game::camera.y);
			destination.w = static_cast<int>(transformComponent->dimension.x * transformComponent->scale);
			destination.h = static_cast<int>(transformComponent->dimension.y * transformComponent->scale);
		}

		void Render() override
		{
			TextureManager::Draw(texture, source, destination, spriteFlip);
		}
	};
}