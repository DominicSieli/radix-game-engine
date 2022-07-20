#include <iostream>

#include "./Map.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./EntityManager.h"
#include "../lib/glm/glm.hpp"
#include "./SpriteComponent.h"
#include "./KeyboardComponent.h"
#include "./ColliderComponent.h"
#include "./TransformComponent.h"
#include "./TextLabelComponent.h"
#include "./ProjectileEmitterComponent.h"

Map* map;
SDL_Event Game::event;
EntityManager entityManager;
SDL_Renderer* Game::renderer;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
AssetManager* Game::assetManager = new AssetManager(&entityManager);

Game::Game()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error Initializing SDL\n";
		return;
	}

	if(TTF_Init() != 0)
	{
		std::cerr << "Error Initializing SDL TTF\n";
		return;
	}

	this->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

	if(this->window == nullptr)
	{
		std::cerr << "Error Creating SDL window\n";
		return;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	if(this->renderer == nullptr)
	{
		std::cerr << "Error Creating SDL Renderer";
		return;
	}

	LoadLevel(0);

	this->running = true;
	return;
}

Game::~Game()
{}

bool Game::Running() const
{
	return this->running;
}

Entity& player(entityManager.AddEntity("player", PLAYER));

void Game::LoadLevel(int levelNumber)
{
	assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 24);

	assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
	assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
	assetManager->AddTexture("projectile-image", std::string("./assets/images/bullet-enemy.png").c_str());

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

	Entity& labelLevelName(entityManager.AddEntity("LabelLevelName", UI));
	labelLevelName.AddComponent<TextLabelComponent>(10, 10, "Level: 1", "charriot-font", WHITE);

	player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.AddComponent<KeyboardComponent>("up", "down", "left", "right", "space");
	player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

	Entity& tank(entityManager.AddEntity("tank", ENEMY));
	tank.AddComponent<TransformComponent>(250, 495, 5, 0, 32, 32, 1);
	tank.AddComponent<SpriteComponent>("tank-image");
	tank.AddComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

	TransformComponent* tankTransform = tank.GetComponent<TransformComponent>();
	Entity& projectile(entityManager.AddEntity("projectile", PROJECTILE));
	projectile.AddComponent<TransformComponent>(tankTransform->position.x+16, tankTransform->position.y+16, 0, 0, 4, 4, 1);
	projectile.AddComponent<SpriteComponent>("projectile-image");
	projectile.AddComponent<ColliderComponent>("PROJECTILE", tankTransform->position.x+16, tankTransform->position.y+16, 4, 4);
	projectile.AddComponent<ProjectileEmitterComponent>(50, 0, 200, true);

	Entity& helipad(entityManager.AddEntity("helipad", OBSTACLE));
	helipad.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
	helipad.AddComponent<SpriteComponent>("heliport-image");
	helipad.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

	Entity& radar(entityManager.AddEntity("radar", UI));
	radar.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radar.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	entityManager.ListEntities();
}

void Game::Input()
{
	SDL_PollEvent(&event);

	switch(event.type)
	{
		case SDL_QUIT: { this->running = false; break; }
		case SDL_KEYDOWN: { if(event.key.keysym.sym == SDLK_ESCAPE) this->running = false; break; }
		default: break;
	}
}

void Game::Update()
{
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.00f;

	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	this->ticksLastFrame = SDL_GetTicks();

	entityManager.Update(deltaTime);

	UpdateCameraMovement();
	CheckCollisions();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
	SDL_RenderClear(this->renderer);

	if(entityManager.IsEmpty() == true)
	{
		return;
	}

	entityManager.Render();

	SDL_RenderPresent(this->renderer);
}

void Game::UpdateCameraMovement()
{
	TransformComponent* playerTransform = player.GetComponent<TransformComponent>();

	camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

	camera.x = (camera.x < 0) ? 0 : camera.x;
	camera.y = (camera.y < 0) ? 0 : camera.y;
	camera.x = (camera.x > camera.w) ? camera.w : camera.x;
	camera.y = (camera.y > camera.h) ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
	CollisionType collisionType = entityManager.CheckCollisions();

	if(collisionType == PLAYER_ENEMY_COLLISION)
	{
		ProcessGameOver();
	}

	if(collisionType == PLAYER_PROJECTILE_COLLISION)
	{
		ProcessGameOver();
	}

	if(collisionType == PLAYER_LEVEL_COMPLETE_COLLISION)
	{
		ProcessNextLevel(1);
	}
}

void Game::ProcessGameOver()
{
	std::cout << "Game Over\n";
	running = false;
}

void Game::ProcessNextLevel(int levelNumber)
{
	std::cout << "Next Level\n";
	running = false;
}

void Game::Destroy()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}