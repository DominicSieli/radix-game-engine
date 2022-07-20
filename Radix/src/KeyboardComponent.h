#pragma once

#include "Game.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

namespace Radix
{
	class KeyboardComponent: public Component
	{
	public:
		std::string upKey;
		std::string downKey;
		std::string leftKey;
		std::string rightKey;
		std::string shootKey;

		SpriteComponent* spriteComponent;
		TransformComponent* transformComponent;

		KeyboardComponent()
		{}

		KeyboardComponent(std::string upKey, std::string downKey, std::string leftKey, std::string rightKey, std::string shootKey)
		{
			this->upKey = SDL_Keycode(upKey);
			this->downKey = SDL_Keycode(downKey);
			this->leftKey = SDL_Keycode(leftKey);
			this->rightKey = SDL_Keycode(rightKey);
			this->shootKey = SDL_Keycode(shootKey);
		}

		std::string SDL_Keycode(std::string key)
		{
			if(key.compare("up") == 0) return "1073741906";
			if(key.compare("down") == 0) return "1073741905";
			if(key.compare("left") == 0) return "1073741904";
			if(key.compare("right") == 0) return "1073741903";
			if(key.compare("space") == 0) return "32";

			return std::to_string(static_cast<int>(key[0]));
		}

		void Initialize() override
		{
			transformComponent = entity->GetComponent<TransformComponent>();
			spriteComponent = entity->GetComponent<SpriteComponent>();
		}

		void Update(float deltaTime) override
		{
			if(Game::event.type == SDL_KEYDOWN)
			{
				int speed = 100;
				std::string keyCode = std::to_string(Game::event.key.keysym.sym);

				if(keyCode.compare(upKey) == 0)
				{
					transformComponent->velocity.x = 0;
					transformComponent->velocity.y = -speed;
					spriteComponent->Play("UpAnimation");
				}

				if(keyCode.compare(downKey) == 0)
				{
					transformComponent->velocity.x = 0;
					transformComponent->velocity.y = speed;
					spriteComponent->Play("DownAnimation");
				}

				if(keyCode.compare(leftKey) == 0)
				{
					transformComponent->velocity.x = -speed;
					transformComponent->velocity.y = 0;
					spriteComponent->Play("LeftAnimation");
				}

				if(keyCode.compare(rightKey) == 0)
				{
					transformComponent->velocity.x = speed;
					transformComponent->velocity.y = 0;
					spriteComponent->Play("RightAnimation");
				}

				if(keyCode.compare(shootKey) == 0)
				{}
			}

			if(Game::event.type == SDL_KEYUP)
			{
				std::string keyCode = std::to_string(Game::event.key.keysym.sym);

				if(keyCode.compare(upKey) == 0)
				{
					transformComponent->velocity.y = 0;
				}

				if(keyCode.compare(downKey) == 0)
				{
					transformComponent->velocity.y = 0;
				}

				if(keyCode.compare(leftKey) == 0)
				{
					transformComponent->velocity.x = 0;
				}

				if(keyCode.compare(rightKey) == 0)
				{
					transformComponent->velocity.x = 0;
				}

				if(keyCode.compare(shootKey) == 0)
				{}
			}
		}
	};
}