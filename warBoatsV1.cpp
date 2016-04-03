#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std; 

//function prototypes:
const int SIZE = 10;
void showBoard(char board[SIZE][SIZE]);
void hideBoat(int boat, char board[SIZE][SIZE]);
void guessBoat(char guess[][SIZE], char target[][SIZE]);
bool checkBoard(char target[][10]);

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
	while ( boatSunk == false)		
	{	
		showBoard(guessBoard);
		cout << endl;
		showBoard(boatBoard);	
		guessBoat(guessBoard, boatBoard);
		boatSunk = !(checkBoard(boatBoard));
	}
	cout << "You sunk my battleship!!" << endl;
	return 0;
}
//hiding the boats
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
void guessBoat(char guess[][SIZE], char target[][SIZE])
{
	while(true)
	{	
		//get coordinates as input	
		char rowLet;	
		int row, col;
		do
		{
			cout << "Row: ";
			cin >> rowLet; //change to int, validate.
			row = rowLet;
			if (row > 64 && row < 75)//uppercase, convert to coordinate.
			{
				row = row - 65;
				break;
			}
			else if(row > 96 && row <107)//lowercase, convert to coordinate
			{
				row = row - 97;
				break;
			}
			else //invalid, get better input. 
			{
				cout << "Invalid input. Please enter a valid row (A-J)" << endl;
				continue;
			}
		} while (false);
		do
		{
			cout << "Column: ";
			cin >> col;
			if (!(col >= 0 && col <= 10))
			{
				cout << "Invalid input. Please enter a valid column (0-10)" << endl;
				continue;
			}
			else
				break;
		}while (false);
		//check on guess board if it was guessed
		if (guess[row][col] != '?')
		{
			cout << "Already guessed. Please enter new coordinates." << endl;
			continue;
		}
		//check on target board if it's a boat, update the boards
		if (target[row][col] == 'X')
		{
			cout << "Hit!" << endl;
			guess[row][col] = 'X';
			target[row][col] = 'H';
			break;
		}
		if (target[row][col] == 'W')
		{
			cout << "Miss." << endl;
			guess[row][col] = 'W';
			break;
		}
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
