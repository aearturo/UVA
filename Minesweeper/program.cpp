#include <cstdio>

int rows;
int columns;
char board[100][101];
int boards;

char charForCell(int row, int column)
{
	if(board[row][column] == '*')
		return '*';

	int total = 0;

	for(int i=(row == 0) ? 0 : row - 1; i<=row+1 && i <rows; i++)
	{
		for(int j=(column == 0) ? 0 : column - 1; j<=column+1 && j <columns; j++)
		{
			if(board[i][j] == '*')
				total ++;
		}
	}

	return '0' + (char)total;
}

bool processOne()
{
	scanf("%d %d", &rows, &columns);

	if(rows == 0)
		return false;

	for(int i=0;i<rows;i++)
	{
		scanf("%s", board[i]);
	}

	if(boards!=1) printf("\n");
	printf("Field #%d:\n", boards++);
	for(int i=0; i < rows; i ++)
	{
		for(int j=0;j<columns;j++)
		{
			board[i][j] = charForCell(i,j);
		}
		printf("%s\n", board[i]);
	}

	return true;
}

int main()
{
	boards = 1;
	while(processOne())
	{
	}

	return 0;
}