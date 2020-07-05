#include <iostream>
#include "GameEngine.hpp"

/*
	Conway's Game of Life by Haider Rauf
	lolis for life
*/


int main()
{
	GameEngine* game_engine = GameEngine::get_instance();
	game_engine->main_loop();
}