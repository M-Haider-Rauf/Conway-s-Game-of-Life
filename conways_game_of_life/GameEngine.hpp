#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

//#include <raylib.h>
#include <unordered_map>
#include "GameState.hpp"

class GameEngine {
public:
	~GameEngine();

	void main_loop();
	bool should_quit;
	const static Color menu_bg;

	static GameEngine* get_instance()
	{
		static GameEngine engine;
		return &engine;
	}

	void quit() { should_quit = true; }

private:
	//Standard Game Loop functions;

	void handle_input();
	void tick();
	void render() const;

	GameState* current_state;

	std::unordered_map<StateId, GameState*> state_machine;

	GameEngine();
};


#endif // !GAME_ENGINE_HPP
