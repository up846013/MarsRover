#pragma once
//class to represent the plateau
class Grid
{
    int MaxX; //size of grid in the x direction
    int MaxY; //size of grid in the y direction

public:

    //sets the initial grid size 
    void SetGridSize(int x, int y);

    //gets grid x and y
    int GetGridX();
    int GetGridY();

};