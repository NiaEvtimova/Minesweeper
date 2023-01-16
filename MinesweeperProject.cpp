#include <iostream>
using namespace std;

int myStrLen(const char *command)
{
	int count = 0;
	while (*command != '\0') 
	{
		count++;
		command++;
	}
	return count;
}

bool myStrCmp(const char *command, const char *inputCommand)
{
	int i = 0;
	bool isSame = true;
	int lenCommand = myStrLen(command);
	int lenInputCommand = myStrLen(inputCommand);
	if (lenCommand != lenInputCommand)
	{
		return false;
	}

	while (i < lenCommand || i < lenInputCommand)
	{
		if (command[i] != inputCommand[i])
		{
			isSame = false;
		}
		if(!isSame)
		{
			break;
		}
		i++;
	}
	return isSame;
}

void validate(int number, int a, int b)
{
	bool isValid = false;
	if (number >= a && number <= b)
	{
		isValid = true;
	}
	while (!isValid)
	{
		cout << "Please enter a valid number." << endl;
		cin >> number;

		if (number >= a && number <= b)
		{
			isValid = true;
		}
	}
}
int main()
{
	int fieldSize;
	cin >> fieldSize;
	validate(fieldSize, 3, 10);

	cout << "Please enter how many mines you want in your game." << endl;
	int mines;
	cin >> mines;
	validate(mines, 1, 3 * fieldSize);

	const int maxSize = 10;
	char field[maxSize][maxSize];
	char shownField[maxSize][maxSize];
	bool isMine[maxSize][maxSize];

	for (int i = 0;i < fieldSize;i++)
	{
		for (int j = 0;j < fieldSize;j++)
		{
			shownField[i][j] = '0';
			field[i][j] = '0';
			isMine[i][j] = 0;
		}
	}

	srand((unsigned)time(NULL));

	for (int i = 0;i < mines;i++)
	{
		int x = rand() % fieldSize;
		int y = rand() % fieldSize;

		while (isMine[x][y])
		{
			x = rand() % fieldSize;
			y = rand() % fieldSize;
		}
		field[x][y] = '*';
		isMine[x][y] = true;
	}

	int countOpenPos = 0;
	int countMarkedMines = 0;
	bool hasLost = false;
	bool hasWon = false;
	while (!hasLost || hasWon)
	{
		cout << "Please enter a command." << endl;
		char command[7];
		cin.ignore();
		cin.getline(command, 7);
		

		while (myStrCmp("open", command) == false && myStrCmp("mark", command) == false && myStrCmp("unmark", command) == false)
		{
			cout << "Please enter a valid command." << endl;
			cin.getline(command, 8);
		}

		cout << "Please enter coordinate x." << endl;
		int x;
		cin >> x;
		validate(x, 0, fieldSize - 1);
		cout << "Please enter coordinate y." << endl;
		int y;
		cin >> y;
		validate(y, 0, fieldSize - 1);
		
		if (myStrCmp("open", command))
		{
			if (field[x][y] == '*')
			{
				hasLost = true;
			}
			else
			{
				shownField[x][y] = '1';
				countOpenPos++;
			}
		}
		else if (myStrCmp("mark", command))
		{
			shownField[x][y] = '*';
			if (field[x][y] == '*')
			{
				countMarkedMines++;
			}
		}
		else if (myStrCmp("unmark", command))
		{
			if (shownField[x][y] == '*')
			{
				shownField[x][y] = '0';
				if (field[x][y] == '*')
				{
					countMarkedMines--;

				}
			}
			else
			{
				cout << "This position hasn't been marked." << endl;
			}
		}
		if (countOpenPos == fieldSize * fieldSize - mines && countMarkedMines == mines) 
		{
			hasWon = true;
		}

		for (int i = 0;i < fieldSize;i++)
		{
			for (int j = 0;j < fieldSize;j++)
			{
				cout << shownField[i][j] << "|";
			}
			cout << endl;
		}

	}

	if (hasLost)
	{
		cout << "You hit a mine! Game over!" << endl;
	}
	
	if (hasWon)
	{
		cout << "Congratilations! You won!" << endl;
	}
}
