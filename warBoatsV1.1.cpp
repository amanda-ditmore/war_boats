#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std; 

//function prototypes:
const int SIZE = 10;
void showBoard(char board[SIZE][SIZE]);
void hideBoat(int boat, char board[SIZE][SIZE]);
void checkCoordinates(int row, int col, char guess[][SIZE], char target[][SIZE]);
bool checkBoard(char target[][10]);
void enterCoords(int*, int*);

int main()
{
	//setting up the boards:		
	char guessBoard[SIZE][SIZE], boatBoard[SIZE][SIZE];
		
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			guessBoard[i][j] = '?';
			boatBoard[i][j] = 'W';
		}
	}
	int boat = 5;
	hideBoat(boat, boatBoard);
	bool boatSunk = false;
	while (!boatSunk)		
	{	
		int row = 0, col = 0;
		showBoard(guessBoard);
		cout << endl;
		showBoard(boatBoard);
		    
		enterCoords(&row, &col);
		
		checkCoordinates(row, col, guessBoard, boatBoard);
		boatSunk = !(checkBoard(boatBoard));
	}
	cout << "You sunk my battleship!!" << endl;
	return 0;
}
//***********************************************
// Computer hides one boat randomly on its board*
//***********************************************
void hideBoat(int boat, char board[SIZE][SIZE]) 
{	
	//make 3 random numbers.
	int seed = time(0);
	srand(seed);
	int num1 = rand(), num2 = rand(), num3 = rand();
	//test: cout << num1 << " " << num2 << " " << num3 << " " << endl;
	//randomly decide if it is vertical or horizontal
	if (num1 % 2 == 0) //horizontal
	{
		//randomly pick an appropriate coordinate
		int row = num2 % (SIZE);
		int col = num3 % (SIZE - boat); 
		//loop through a horizontal pattern to hide on the boat board.
		for (int i = 0; i < boat; ++i)
		{
			board[row][col] = 'X';
			++col;
		}
	}
	else //go vertical	
	{	
		//randomly pick an appropriate coordinate
		int row = num2 % (SIZE - boat);
		int col = num3 % (SIZE); 		
		//loop through a vertical pattern to hide on the boat board.
		for (int i = 0; i < boat; ++i)
		{
			board[row][col] = 'X';
			++row;
		}
	}
}
//************************************
//This will display any of the boards*
//************************************	
void showBoard(char board[SIZE][SIZE])
{
	cout << " 0123456789" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << static_cast<char>('A' + i);
		for (int j = 0; j < SIZE; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

void enterCoords(int *row, int *col)
{
	char rowCoords;
	int columnCoords;
		
	cout << "Enter coords (l nn): ";
	cin >> rowCoords >> columnCoords;
	
	//convert char ASCII to row int
	*row = rowCoords-97;
	*col = columnCoords;
}

void checkCoordinates(int row, int col, char guess[][SIZE], char target[][SIZE])
{
	
	//check on guess board if it was guessed
	if (guess[row][col] != '?')
	{
		cout << "Already guessed. Please enter new coordinates." << endl;
		enterCoords(&row, &col);
	}
	//check on target board if it's a boat, update the boards
	else if (target[row][col] == 'X')
	{
		cout << "Hit!" << endl;
		guess[row][col] = 'X';
		target[row][col] = 'H';
	}
	else if (target[row][col] == 'W')
		{
			cout << "Miss." << endl;
			guess[row][col] = 'W';
		}
}
bool checkBoard(char target[][10])
//this function loops through the board to see if there are still x's
//check each spot. if there is an x, this returns true. if there is no x, false.  
{
	bool targetX = false;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (target[i][j] == 'X')
			{
				targetX = true;
				break;
			}
		}
		if (targetX == true)		
		{
		break;
		}
	}
	return targetX;
}

/*to do: the errors for out of range during the guessing loop aren't going the way I want. example output: 
Row: r
Invalid input. Please enter a valid row (A-J)
Column: 11
Invalid input. Please enter a valid column (0-10)
Already guessed. Please enter new coordinates.
Row: F
Column: 3

Hit!
Maybe drawing a diagram will help?
does there need to be the outer while loop of the guess function?
maybe try having a get coordinates function that loops till there are valid coordinates, 
and then a separate function that checks that spot on the board (then we would only need to pass the one spot instead of both. 
Can a function call itself?
Add a counter for the guesses/turns */
