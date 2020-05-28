#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

//#include <raylib.h>
#include <unordered_map>
#include "GameState.hpp"

class GameEngine {
public:
	~GameEngine();

	void main_loop();
	static bool should_quit;
	const static Color menu_bg;

	static GameEngine* get_instance()
	{
		if (!instance) {
			instance = new GameEngine;
		}
		return instance;
	}

private:
	//Standard Game Loop functions;

	void handle_input();
	void tick();
	void render() const;

	GameState* current_state;

	static std::unordered_map<StateId, GameState*> states_cache;
	static GameEngine* instance;

	GameEngine();
};


#endif // !GAME_ENGINE_HPP
