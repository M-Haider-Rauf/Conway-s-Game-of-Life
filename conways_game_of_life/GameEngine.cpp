#include "GameEngine.hpp"


#include <raylib.h>

#include "Constants.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"
#include "About.hpp"

bool GameEngine::should_quit = false;
const Color GameEngine::menu_bg = { 255, 205, 184, 255 };

GameEngine::GameEngine()
	: current_state (nullptr)
	, state_machine()
{
	InitWindow(WIN_W, WIN_H, "Conway's Game of Life by HaiderRauf69");
	SetTargetFPS(60);
	
	state_machine.insert({ StateId::Playing, new PlayState });
	state_machine.insert({ StateId::Menu, new MenuState });
	state_machine.insert({ StateId::About, new AboutState });
	this->current_state = state_machine[StateId::Menu];
}

GameEngine::~GameEngine()
{
	for (auto it = state_machine.begin(); it != state_machine.end(); ++it) {
		delete it->second;
	}
	CloseWindow();
}

//----------------------------------------------------

void GameEngine::handle_input()
{
	if (WindowShouldClose()) should_quit = true;
	if (IsKeyPressed(KEY_C)) TakeScreenshot(TextFormat("%d.bmp", GetTime()));
	current_state->handle_input();
}

void GameEngine::tick()
{
	current_state->tick();

	if (current_state->get_next_state() != StateId::Null) {
		current_state = state_machine[current_state->get_next_state()];
		current_state->set_next_state(StateId::Null);
	}
}

void GameEngine::render() const
{
	BeginDrawing();

	switch (current_state->id()) {
	case StateId::Menu:
		ClearBackground(menu_bg);
		break;

	default:
		ClearBackground(BLACK);
		break;
	}

	current_state->render();
	
	EndDrawing();
}


//------------------------------------------

void GameEngine::main_loop()
{
	//Ah yes, the Big 3 of a game loop
	while (!should_quit) {
		handle_input();
		tick();
		render();
	}
}
