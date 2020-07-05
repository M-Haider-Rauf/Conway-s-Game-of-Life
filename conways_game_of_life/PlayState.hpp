#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include "GameState.hpp"
#include "Constants.hpp"
#include "Grid.hpp"

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
	Grid<GRID_ROWS, GRID_COLS> grid;
	static bool paused;
	static bool started;
	static double start_time;
	static double threshold;
	static unsigned generation;

	void save_grid() const;
	void load_grid();


};



#endif // !PLAY_STATE_HPP
