#include "states.h"
#include "statesManager.h"
#include "Game.h"
#include "GameObject.h"
#include <iostream>
float timer = 0.0;
//begin title screen
void TitleState::Enter()
{
	std::cout << "entering TitleState" << std::endl;
	timer = 0;
}

void TitleState::Update(float deltaTime)
{

	if (timer > 4)
	{
		std::cout << "changing to game state" << std::endl;
		StateManager::ChangeState(new GameState());//change to new game state
	}
	timer += deltaTime;
}

void TitleState::Render()
{
	std::cout << "rendering title state" << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void TitleState::Exit()
{
	std::cout << "exiting title state..." << std::endl;

}

//end title state

//begin game state
void GameState::Enter()//used for initilization
{

	std::cout << "entering game state" << std::endl;

	m_GameObjects.push_back(new GameObject(100, 100, 30, 30, 255, 0, 0, 255));
	m_GameObjects.push_back(new GameObject(200, 100, 30, 30, 255, 0, 0, 255));
	m_GameObjects.push_back(new GameObject(300, 100, 30, 30, 255, 0, 0, 255));

}

void GameState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))
	{
		StateManager::ChangeState(new TitleState());
	}

	else if (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
		StateManager::PushState(new PauseState());
	}
	else
	{
		if (GameInstance.KeyDown(SDL_SCANCODE_W))
		{

		}


	}
}

void GameState::Render()
{
	std::cout << "rendering game sate..." << std::endl;

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
	SDL_RenderClear(pRenderer);




}

void GameState::Exit()
{
	std::cout << "exiting game state..." << std::endl;
}

void GameState::Resume()
{
	std::cout << "resuming game state..." << std::endl;
}
//end game state

//start pause state 

void PauseState::Enter()
{
	std::cout << "entering pause state" << std::endl;
}

void PauseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		StateManager::popState;
	}
}

void PauseState::Render()
{
	std::cout << "rendering Pause State" << std::endl;
	//first we render the game state 
	StateManager::GetStates().front()->Render();
	//now we render the rest of pause state 
	SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		StateManager::ChangeState(new GameState());
	}


}

void PauseState::Exit()
{
	std::cout << "exiting pause state..." << std::endl;
}
//end pause state 
