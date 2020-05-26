#include "GameEngine.hpp"


#include <raylib.h>

#include "Constants.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"
#include "About.hpp"

std::unordered_map<StateId, GameState*> GameEngine::states_cache;
bool GameEngine::should_quit = false;
const Color GameEngine::menu_bg = { 255, 205, 184, 255 };

GameEngine::GameEngine()
	: current_state (nullptr)
	, next_state (StateId::Null)
{
	InitWindow(WIN_W, WIN_H, "Conway's Game of Life by HaiderRauf69");
	SetTargetFPS(60);
	

	states_cache.insert({ StateId::Playing, new PlayState });
	states_cache.insert({ StateId::Menu, new MenuState });
	states_cache.insert({ StateId::About, new AboutState });
	this->current_state = states_cache[StateId::Menu];
}

GameEngine::~GameEngine()
{
	for (auto it = states_cache.begin(); it != states_cache.end(); ++it) {
		delete it->second;
	}
	CloseWindow();
}

//----------------------------------------------------

void GameEngine::handle_input()
{
	if (WindowShouldClose()) should_quit = true;
	current_state->handle_input();
}

void GameEngine::tick()
{
	current_state->tick();
}

void GameEngine::render() const
{
	BeginDrawing();

	if (current_state->id() == StateId::Menu) {
		ClearBackground(GameEngine::menu_bg);
	}
	else {
		ClearBackground(BLACK);
	}

	current_state->render();

	EndDrawing();
}


//------------------------------------------

void GameEngine::main_loop()
{
	while (!should_quit) {
		handle_input();
		tick();

		next_state = current_state->get_next_state();
		current_state->set_next_state(StateId::Null);
		if (next_state != StateId::Null) {
			current_state = states_cache[next_state];
			next_state = StateId::Null;
			//current_state->on_enter();
		}

		render();
	}
}
