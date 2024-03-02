#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "./constants.h"

namespace Radix
{
	class AssetManager;

	class Game
	{
	private:
		bool running = false;
		SDL_Window* window = nullptr;

	public:
		Game();
		~Game();

		int ticksLastFrame = 0;
		bool Running() const;
		static SDL_Event event;
		static SDL_Rect camera;
		static SDL_Renderer* renderer;
		static AssetManager* assetManager;

		void LoadLevel(int levelNumber);
		void Input();
		void Update();
		void Render();
		void UpdateCameraMovement();
		void CheckCollisions();
		void ProcessGameOver();
		void ProcessNextLevel(int levelNumber);
		void Destroy();
	};
}