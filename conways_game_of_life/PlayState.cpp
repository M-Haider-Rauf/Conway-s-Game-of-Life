#include "PlayState.hpp"

#include <iostream>
#include <fstream>
#include <string>


#define BLOCK_COLOR RED


PlayState::PlayState()
	: GameState(StateId::Playing)
	, curr_state(new bool[GRID_COLS * GRID_ROWS] { 0 })
{
}

PlayState::~PlayState()
{
	delete[] curr_state;
}

void PlayState::handle_input()
{
	static constexpr double frame_time = 1 / 60.0;
	static Vector2 prev_pos = {};
	if (!started) {

		if (IsKeyPressed(KEY_S)) {
			started = true;
		}

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			auto position = GetMousePosition();
			position.x /= BLOCK_SIZE;
			position.y /= BLOCK_SIZE;

			position.x = (int)(position.x);
			position.y = (int)(position.y);

			if (!(prev_pos.x == position.x && prev_pos.y == position.y)) {
				grid_at(curr_state, position.x, position.y) = !grid_at(curr_state, position.x, position.y);
			}
			prev_pos = position;
		}
	}

	if (IsKeyPressed(KEY_P)) paused = !paused;
	else if (IsKeyPressed(KEY_UP)) threshold -= 0.07;
	else if (IsKeyPressed(KEY_DOWN)) threshold += 0.07;
	else if (IsKeyPressed(KEY_R)) this->reset();
	else if (IsKeyPressed(KEY_BACKSPACE)) this->set_next_state(StateId::Menu);

	if (threshold > 1.0) threshold = 1.0;
	else if (threshold < frame_time) threshold = frame_time;
}

void PlayState::tick()
{	
	if (!started || paused) return;

	if (GetTime() - start_time >= threshold) {
		start_time = GetTime();
	}
	else {
		return;
	}

	bool* next_state = new bool[GRID_COLS * GRID_ROWS] {};
	std::memcpy(next_state, curr_state, sizeof *curr_state * GRID_COLS * GRID_ROWS);

	for (int y = 0; y < GRID_ROWS; ++y) {
		for (int x = 0; x < GRID_COLS; ++x) {
			//calculate 8-way neighbours
			int alive_count = 
				grid_at(curr_state, x + 1, y) + grid_at(curr_state, x - 1, y) + 
				grid_at(curr_state, x, y + 1) + grid_at(curr_state, x, y - 1) +
				grid_at(curr_state, x + 1, y + 1) + grid_at(curr_state, x - 1, y - 1) + 
				grid_at(curr_state, x - 1, y + 1) + grid_at(curr_state, x + 1, y - 1);

			//calculate next state
			if (grid_at(curr_state, x, y) && (alive_count < 2 || alive_count > 3)) {
				grid_at(next_state, x, y) = false;

			}
			else if (alive_count == 3) {
				grid_at(next_state, x, y) = true;
			}
		}
	}

	//update current state
	delete[] this->curr_state;
	this->curr_state = next_state;
	++generation;
}

void PlayState::render() const
{
	for (int y = 0; y < GRID_ROWS; ++y) {
		for (int x = 0; x < GRID_COLS; ++x) {
			if (grid_at(curr_state, x, y)) {
				DrawRectangle(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_COLOR);
			}
		}
	}
	draw_lines();
	DrawText(TextFormat("Generation: %d", generation), 20, GRID_H + 4, 25, BLUE);
	DrawText(TextFormat("Threshold: %.2f", threshold), GRID_W - 300, GRID_H + 4, 25,  BLUE);

	if (!started) {
		DrawText("***Press S to start***", 500, GRID_H + 4, 25, BLUE);
	}
	else if (paused) {
		DrawText("PAUSED! Press P to resume...", 400, 300, 50, BLUE);
	}
	else {
		DrawText("Simulation running... Press R to reset", 400, GRID_H + 4, 25, BLUE);
	}
	
}

void PlayState::on_enter()
{

	std::memset(curr_state, 0x0, sizeof *curr_state * GRID_COLS * GRID_ROWS);

	start_time = 0;
	threshold = 0.2;

	paused = false;
	started = false;
	start_time = 0;
	generation = 0;
}


void PlayState::draw_hor_line(int x, int y, Color color)
{
	DrawLine(x, y, GRID_W - x, y, color);
}

void PlayState::draw_vert_line(int x, int y, Color color)
{
	DrawLine(x, y, x, GRID_H - y, color);
}

void PlayState::draw_lines()
{
	static constexpr Color grid_color = { 127, 127, 127, 255 };
	for (size_t i = 0; i < GRID_ROWS + 1; ++i) {
		draw_hor_line(0, i * BLOCK_SIZE, grid_color);
	}
	for (size_t i = 0; i < GRID_COLS; ++i) {
		draw_vert_line(i * BLOCK_SIZE, 0, grid_color);
	}
}


void PlayState::reset()
{
	memset(curr_state, 0, GRID_COLS * GRID_ROWS * sizeof *curr_state);
	paused = false;
	started = false;
	start_time = 0.0;
	generation = 0;
}

bool& grid_at(bool* arr, int x, int y)
{
	//wrap around behaiour
	if (x < 0) x = GRID_COLS - 1;
	else if (x >= GRID_COLS) x = 0;

	if (y < 0) y = GRID_ROWS - 1;
	else if (y >= GRID_ROWS) y = 0;

	return arr[y * GRID_COLS + x];
}
