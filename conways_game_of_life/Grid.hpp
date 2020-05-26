#ifndef GRID_HPP
#define GRID_HPP

#include <raylib.h>
#include <string.h>


template <int R, int C>
class Grid {
public:
	Grid() : arr{} {}
	bool& operator()(int x, int y)
	{
		warp(&x, &y);
		return arr[y][x];
	}

	bool operator()(int x, int y) const
	{
		warp(&x, &y);
		return arr[y][x];
	}

private:
	static void warp(int* x, int* y)
	{
		if (*x < 0) *x = C - 1;
		else if (*x > C - 1) *x = 0;

		if (*y < 0) *y = R - 1;
		else if (*y > R - 1) *y = 0;
	}

	bool arr[R][C];
};

#endif // !GRID_HPP
