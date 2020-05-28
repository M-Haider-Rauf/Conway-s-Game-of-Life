#include <iostream>
#include "GameEngine.hpp"

int main()
{
	GameEngine* game_engine = GameEngine::get_instance();
	game_engine->main_loop();
}