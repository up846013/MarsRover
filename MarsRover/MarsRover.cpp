// MarsRover.cpp
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include "coordinate.h"
#include "Grid.h"

using namespace std;

Grid Plateau; //the terrain the rovers are permitted to explore


class Rover
{
    //rover variables
    int CurrentX = 0;  //x coordiante
    int CurrentY = 0; //y coordiante
    char Direction = 'N'; //direction it is facing
    string Name; //rovers name
    string Instructions; //rovers instruction set to be executed
    list<Coordinate> CollisionPoints;

public:
    //used to name the rover
    void SetName(string name)
    {
        Name = name;
    }

    //used to initilalise the rovers starting location and direction
    void SetInitialPosAndDir(int x, int y, char Dir)
    {
        CurrentX = x;
        CurrentY = y;
        Direction = Dir;

    }

    int GetXPosition() //gets rover x
    {
        return CurrentX;
    }

    int GetYPosition() //gets rover y
    {
        return CurrentY;
    }

    int GetDirection() //gets rover direction
    {
        return Direction;
    }

    void SetCollisionAvoidance(list<Coordinate> AvoidList)
    {
        //remove this rovers current location
        for (Coordinate TempCoord : AvoidList)
        {
            if (TempCoord.X != CurrentX || TempCoord.Y != CurrentY)
            {
                //rover removes itself from collision list/any rovers on same tile such as the start tile
                CollisionPoints.push_back(Coordinate(TempCoord.X, TempCoord.Y));
            }
        }
    }

    //prints the current location and direction of the rover
    void PrintStatus()
    {
        cout << Name << endl;
        cout << CurrentX << " " << CurrentY << " " << Direction << endl;
    }

    //Stores instructions for later use
    void SetInstructions(string InstructionString)
    {
        Instructions = InstructionString;
    }

    //used to retrieve stored instructions
    string GetInstructions()
    {
        return Instructions;
    }

    //executes the instructions given to rover
    void RoverInstructions(string InstructionString)
    {
        Instructions = InstructionString; //the instructions
        for (int CountVar = 0; CountVar < Instructions.length(); CountVar++) //loops through instructions to decode them
        {
            //identifies instruction and decodes it
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

                //if erroneous then rover prints its current position and reason why it cant execute
            default:
                cout << "ERROR: INSTRUCTION NOT VALID" << endl;
                PrintStatus();
                break;
            }
        }
    }

private:

    void RoverForward()
    {
        //switch for moving the rover in the direction its facing
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
            //if erroneous then rover prints its current position and reason why it cant execute
            cout << "ERROR: POSITION NOT VALID" << endl;
            PrintStatus();
            break;
        }


        if (CurrentX < 0 || CurrentX > Plateau.GetGridX())
        {
            //if erroneous then rover prints its current position and reason why it cant execute
            cout << "ERROR: COORDINATE X HAS EXCEEDED PLATEAU BOUNDS" << endl;
            PrintStatus();
        }
        if (CurrentY < 0 || CurrentY > Plateau.GetGridY())
        {
            //if erroneous then rover prints its current position and reason why it cant execute
            cout << "ERROR: COORDINATE Y HAS EXCEEDED PLATEAU BOUNDS" << endl;
            PrintStatus();
        }

        //searches collision list to see if a crash has occurred
        for (Coordinate TempCoord : CollisionPoints)
        {
            if (CurrentX == TempCoord.X && CurrentY == TempCoord.Y)
            {
                //rover has crashed
                cout << "ERROR: ROVER HAS CRASHED INTO ANOTHER ROVER" << endl;
                PrintStatus();
            }
        }

    }

    void RoverLeft()
    {
        //rotates rover direction anticlockwise using a switch
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
            //if erroneous then rover prints its current position and reason why it cant execute
            cout << "ERROR: DIRECTION NOT VALID" << endl;
            PrintStatus();
            break;
        }
    }
    
    void RoverRight()
    {
        //rotates rover direction clockwise using a switch
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
            //if erroneous then rover prints its current position and reason why it cant execute
            cout << "ERROR: DIRECTION NOT VALID" << endl;
            PrintStatus();
            break;
        }
    }

};

class RoverManager
{
public:
    list<Rover> RoverList = {}; //list of all rovers
    list<Coordinate> RoverPositions = {}; //list of all rover coordinates

    void InitialRoverPositions()
    {
        RoverPositions.clear();
        for (Rover TempRover : RoverList)
        {
            RoverPositions.push_back(Coordinate(TempRover.GetXPosition(), TempRover.GetYPosition())); //adds rover coords to list
        }
    }

    void UpdateRoverPosition(Coordinate NewPosition)
    {
        RoverPositions.pop_front();
        RoverPositions.push_back(NewPosition);
    }

    void ExecuteInstructions()
    {
        for (Rover TempRover : RoverList) //loops through rover list to execute their instructions in order
        {
            TempRover.SetCollisionAvoidance(RoverPositions); //gives positions to current rover needing to execute instructions
            TempRover.RoverInstructions(TempRover.GetInstructions()); //executes current rover instructions using their stored instructions
            TempRover.PrintStatus();
            UpdateRoverPosition(Coordinate(TempRover.GetXPosition(), TempRover.GetYPosition())); //Checks positions of rovers
        }
    }

};



int main()
{
    //variables
    ifstream InputFile; //stream of file containing all rover positions and instructions
    Rover TempRover; //a temporary rover entity for adding/accessing rovers in the main list 
    RoverManager RoverControll; //controller for rovers, will test for collision etc

    int InputX; //variable for retrieving the x coord from the file
    int InputY; //variable for retrieving the y coord from the file
    char InputDirection; //variable for retrieving the orientation from the file
    string Instructions; //variable for retrieving the rover instructions from the file

    InputFile.open("InputFile.txt"); //opens input file 

    //Getting Grid max boundary for x and y
    InputFile >> InputX;
    InputFile >> InputY;
    //setting the grid size using x and y boundaries
    Plateau.SetGridSize(InputX, InputY);


    //loops through the input file and sets up each rover, 
    //the rovers should all have their x, y, direction and instructions in that order
    int RoverNameCount = 0; //set to 0 
    do
    {
        RoverNameCount += 1; //rover count incremented so first rover is rover1
        InputFile >> InputX;
        InputFile >> InputY;
        InputFile >> InputDirection;
        InputFile >> Instructions;
        //after information is extracted it is assigned to temp rover
        TempRover.SetInitialPosAndDir(InputX, InputY, InputDirection); //sets initial rover position and orientation
        TempRover.SetInstructions(Instructions); //stores instructions
        //temprovers name is set programatically to be "rover1" and the number will accend for each rover deployed
        string TempName = "Rover";
        TempName += to_string(RoverNameCount);
        TempRover.SetName(TempName);
        //temprover is added to the list of rovers and will be uniquely identifiable by its name
        RoverControll.RoverList.push_back(TempRover);
    } while (!InputFile.eof()); //when end of file is reached then it moves on to executing the instructions of each rover

    RoverControll.InitialRoverPositions(); //sets initial position of rovers
    RoverControll.ExecuteInstructions(); //executes rover instructions sequentially
}

