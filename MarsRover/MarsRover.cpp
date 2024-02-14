// MarsRover.cpp
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//class to represent the plateau
class Grid
{
    int MaxX;
    int MaxY;

public:
    
    void SetGridSize(int x, int y)
    {
        MaxX = x;
        MaxY = y;
    }

    void PrintGridSize()
    {
        cout << MaxX << " " << MaxY << endl;
    }
};

class Rover
{
    int CurrentX = 0;
    int CurrentY = 0;
    char Direction = 'N';
    string Name;
    string Instructions;

public:
    void SetName(string name)
    {
        Name = name;
    }

    void SetInitialPosAndDir(int x, int y, char Dir)
    {
        CurrentX = x;
        CurrentY = y;
        Direction = Dir;

    }

    void PrintStatus()
    {
        cout << Name << endl;
        cout << CurrentX << " " << CurrentY << " " << Direction << endl;
    }

    void RoverInstructions(string InstructionString)
    {
        Instructions = InstructionString;
        for (int CountVar = 0; CountVar < Instructions.length(); CountVar++)
        {
            switch (Instructions[CountVar])
            {
            case'M':
                RoverForward();
                break;

            case'L':
                RoverLeft();
                break;

            case'R':
                RoverRight();
                break;

            default:
                cout << "ERROR: INSTRUCTION NOT VALID" << endl;
                break;
            }
        }
    }

private:

    void RoverForward()
    {
        switch (Direction)
        {
        case'N':
            CurrentY++;
            break;

        case'E':
            CurrentX++;
            break;

        case'S':
            CurrentY--;
            break;

        case'W':
            CurrentX--;
            break;

        default:
            cout << "ERROR: POSITION NOT VALID" << endl;
            break;
        }

        if (CurrentX < 0 || CurrentX > 5)
        {
            cout << "ERROR: COORDINATE X HAS EXCEEDED PLATEAU BOUNDS" << endl;
        }
        if (CurrentY < 0 || CurrentY > 5)
        {
            cout << "ERROR: COORDINATE Y HAS EXCEEDED PLATEAU BOUNDS" << endl;
        }
    }

    void RoverLeft()
    {
        switch (Direction)
        {
        case'N':
            Direction = 'W';
            break;

        case'E':
            Direction = 'N';
            break;

        case'S':
            Direction = 'E';
            break;

        case'W':
            Direction = 'S';
            break;

        default:
            cout << "ERROR: DIRECTION NOT VALID" << endl;
            break;
        }
    }
    
    void RoverRight()
    {
        switch(Direction)
        {
        case'N':
            Direction = 'E';
            break;

        case'E':
            Direction = 'S';
            break;

        case'S':
            Direction = 'W';
            break;

        case'W':
            Direction = 'N';
            break;

        default:
            cout << "ERROR: DIRECTION NOT VALID" << endl;
            break;
        }
    }

};



int main()
{
    //variables
    Grid Plateau;
    ifstream InputFile;
    Rover Rover1;
    Rover Rover2;

    int InputX;
    int InputY;
    char InputDirection;
    string Instructions;

    Rover1.SetName("Rover1");
    Rover2.SetName("Rover2");

    InputFile.open("InputFile.txt");

    //Getting Grid max boundary
    InputFile >> InputX;
    InputFile >> InputY;
    Plateau.SetGridSize(InputX, InputY);

    //Gets rover 1 data from input file
    InputFile >> InputX;
    InputFile >> InputY;
    InputFile >> InputDirection;
    InputFile >> Instructions;
    Rover1.SetInitialPosAndDir(InputX, InputY, InputDirection); //sets initial rover 1 position and orientation
    Rover1.RoverInstructions(Instructions); //executes rover 1 instructions


    //gets rover 2 data from input file
    InputFile >> InputX;
    InputFile >> InputY;
    InputFile >> InputDirection;
    InputFile >> Instructions;
    Rover2.SetInitialPosAndDir(InputX, InputY, InputDirection); //sets initial rover 2 position and orientation
    Rover2.RoverInstructions(Instructions); //executes rover 2 instructions

    //displays current and final position of rovers
    Rover1.PrintStatus();
    Rover2.PrintStatus();
}

