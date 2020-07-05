#include "PlayState.hpp"

#include <iostream>
#include <fstream>
#include <string>

#define BLOCK_COLOR RED

bool PlayState::paused = false;
bool PlayState::started = false;
double PlayState::start_time = 0;
double PlayState::threshold = 0.2;
unsigned PlayState::generation = 0;

PlayState::PlayState()
	: GameState(StateId::Playing)
	, grid {}
{
	start_time = 0;
}

PlayState::~PlayState()
{
}

void PlayState::handle_input()
{
	static constexpr double frame_time = 1 / 60.0;
	static Vector2 prev_pos = {};
	if (!started) {

		if (IsKeyPressed(KEY_S)) {
			started = true;
		}
		else if (IsKeyPressed(KEY_F2)) {
			this->save_grid();
		}
		else if (IsKeyPressed(KEY_F3)) {
			this->load_grid();
		}

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			auto position = GetMousePosition();
			position.x /= BLOCK_SIZE;
			position.y /= BLOCK_SIZE;

			position.x = (int)(position.x);
			position.y = (int)(position.y);

			if (!(prev_pos.x == position.x && prev_pos.y == position.y)) {
				grid(position.x, position.y) = !grid(position.x, position.y);
			}
			prev_pos = position;
		}
	}

	if (IsKeyPressed(KEY_P)) paused = !paused;
	else if (IsKeyPressed(KEY_UP)) threshold -= 0.07;
	else if (IsKeyPressed(KEY_DOWN)) threshold += 0.07;
	else if (IsKeyPressed(KEY_R)) this->reset();

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
	auto temp_grid(grid);

	for (int y = 0; y < GRID_ROWS; ++y) {
		for (int x = 0; x < GRID_COLS; ++x) {
			int alive_count = grid(x + 1, y) + grid(x - 1, y) + grid(x, y + 1) + grid(x, y - 1) +
				grid(x + 1, y + 1) + grid(x - 1, y - 1) + grid(x - 1, y + 1) + grid(x + 1, y - 1);
			if (grid(x, y)) {
				if (alive_count == 2 || alive_count == 3) {
					temp_grid(x, y) = true;
				}
				else {
					temp_grid(x, y) = false;
				}
			}
			else {
				if (alive_count == 3) {
					temp_grid(x, y) = true;
				}
				else {
					temp_grid(x, y) = false;
				}
			}
		}
	}

	this->grid = temp_grid;
	++generation;
}

void PlayState::render() const
{
	for (int y = 0; y < GRID_ROWS; ++y) {
		for (int x = 0; x < GRID_COLS; ++x) {
			if (grid(x, y)) {
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
	grid = Grid<GRID_ROWS, GRID_COLS>();

	start_time = 0;

	PlayState::paused = false;
	PlayState::started = false;
	PlayState::start_time = 0;
	PlayState::threshold = 0.2;
	PlayState::generation = 1;
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
	static constexpr Color grid_color = { 130, 130, 130, 180 };
	for (size_t i = 0; i < GRID_ROWS + 1; ++i) {
		draw_hor_line(0, i * BLOCK_SIZE, grid_color);
	}
	for (size_t i = 0; i < GRID_COLS; ++i) {
		draw_vert_line(i * BLOCK_SIZE, 0, grid_color);
	}
}

void PlayState::load_grid()
{
	std::ifstream fin("grid.txt");
	std::string grid_cell;

	memset(&grid(0, 0), 0, GRID_COLS * GRID_ROWS * sizeof(grid(0, 0)));

	while (std::getline(fin, grid_cell)) {
		int index = grid_cell.find(',');
		int x = std::stoi (grid_cell.substr(0, index));
		int y = std::stoi(grid_cell.substr(index + 1));
		grid(x, y) = true;
	}
}

void PlayState::save_grid() const
{
	std::ofstream fout("grid.txt");
	if (!fout) throw "Not file opened";
	for (size_t i = 0; i < GRID_ROWS; ++i) {
		for (size_t j = 0; j < GRID_COLS; ++j) {
			if (grid(i, j)) {
				fout << i << "," << j << "\n";
			}
		}
	}
}


void PlayState::reset()
{
	memset(&grid(0, 0), 0, GRID_COLS * GRID_ROWS);
	paused = false;
	started = false;
	start_time = 0.0;
	generation = 0;
}
