#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include "GameState.hpp"
#include "Constants.hpp"

class PlayState : public GameState {
public:
	PlayState();
	~PlayState();

	void handle_input() override;
	void tick() override;
	void render() const override;
	void on_exit() override {};
	void on_enter() override;

	void reset();
	static void draw_hor_line(int x, int y, Color color = BLACK);
	static void draw_vert_line(int x, int y, Color color = BLACK);
	static void draw_lines();

private:
	static bool paused;
	static bool started;
	static double start_time;
	static double threshold;
	static unsigned generation;
	bool* curr_state = nullptr;

};

bool& grid_at(bool* arr, int x, int y);



#endif // !PLAY_STATE_HPP
