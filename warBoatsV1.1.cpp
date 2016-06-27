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
int getCol();
int getRow();

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
		int row, col;
		showBoard(guessBoard);
		cout << endl;
		showBoard(boatBoard);
		row = getRow();
		col = getCol();	
		checkCoordinates(row, col, guessBoard, boatBoard);
		boatSunk = !(checkBoard(boatBoard));
	}
	cout << "You sunk my battleship!!" << endl;
	return 0;
}



void hideBoat(int boat, char board[SIZE][SIZE]) 
// Computer hides one boat randomly on its board
{	
	//make 3 random numbers.
	int seed = time(0);
	srand(seed);
	int num1 = rand(), num2 = rand(), num3 = rand();

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
	else //vertical	
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


void showBoard(char board[SIZE][SIZE])
//This will display any of the boards	
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

int getRow ()
//gets the row to fire at this turn. 
{
	char rowLet;	
	int row;
	bool validRow = false;
	while (!validRow)
	{
		cout << "Row: ";
		cin >> rowLet; //change to int, validate.
		row = rowLet;
		if (row > 64 && row < 75)//uppercase, convert to coordinate.
		{
			row = row - 65;
			validRow = true;
			return row;
		}
		else if(row > 96 && row <107)//lowercase, convert to coordinate
		{
			row = row - 97;
			validRow = true;
			return row;
		}
		else //invalid row, get better input. 
		{
			cout << "Invalid input. Please enter a valid row (A-J)" << endl;
		}
	}		
}

int getCol()
//returns the column to fire at this turn.
{
	int col;
	bool validCol = false;
	while (!validCol)
	{		
		cout << "Column: ";
		cin >> col;
		if (!(col >= 0 && col <= 10))
		{
			cout << "Invalid input. Please enter a valid column (0-10)" 
				 << endl;			
		}	
		else
		{
			validCol = true;
			return col;
		}
	}
}
void checkCoordinates(int row, int col, char guess[][SIZE], char target[][SIZE])
{
	
	//check on guess board if it was guessed
	if (guess[row][col] != '?')
	{
		cout << "Already guessed. Please enter new coordinates." << endl;
		row = getRow();
		col = getCol();
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
