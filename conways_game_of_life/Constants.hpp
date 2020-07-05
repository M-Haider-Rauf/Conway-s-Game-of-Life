#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

constexpr unsigned BLOCK_SIZE = 20u;
constexpr unsigned GRID_H = 600u;
constexpr unsigned GRID_W = 1300u;
constexpr unsigned WIN_W = GRID_W;
constexpr unsigned WIN_H = GRID_H + 3 * BLOCK_SIZE;
constexpr unsigned GRID_ROWS = GRID_H / BLOCK_SIZE;
constexpr unsigned GRID_COLS = GRID_W / BLOCK_SIZE;


#endif // !CONSTANTS_HPP
