#include "Grid.h"

void Grid::SetGridSize(int x, int y)
{
    MaxX = x;
    MaxY = y;
}

int Grid::GetGridX()
{
	return MaxX;
}

int Grid::GetGridY()
{
    return MaxY;
}