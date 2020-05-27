#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <raylib.h>
#include <iostream>

enum struct StateId {
	Null, Playing, Menu, About
};


class GameState {
public:
	GameState(StateId = StateId::Null);
	virtual ~GameState();

	virtual void handle_input() = 0;
	virtual void tick() = 0;
	virtual void render() const = 0;
	virtual void on_exit() = 0;
	virtual void on_enter() = 0;

	//void reset();

	StateId id() const { return state_id; }
	StateId get_next_state() const { return next_state_if; }
	void set_next_state(StateId id) { next_state_if = id; }

private:
	StateId state_id;
	StateId next_state_if;
};


#endif // !GAME_STATE_HPP
