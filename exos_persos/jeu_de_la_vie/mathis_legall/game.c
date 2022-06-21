#include "game.h"

int** mallocGrid(int n)
{
	int i;

	int** grid = (int**)malloc(n*sizeof(int*));
	
	for (i=0; i<n; i++)
	{
		grid[i] = (int*)malloc(n*sizeof(int));
	}

	return grid;
}

void initGrid(int n, int** grid)
{
	int i,j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void printGrid(int n, int** grid)
{
	int i,j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			printf("%d\t", grid[i][j]);
		}
		printf("\n");
	}
}

void newCell(int n, int i, int j, int** grid, int** copyGrid)
{
	int sumNeighbors;

	if(grid[i][j] == 1)
	{
		if (i == 0)
		{
			if (j == 0)
			{
				sumNeighbors = grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
				if(survive[sumNeighbors] == 1)
				{
					copyGrid[i][j] = 1;
				}
				else
				{
					copyGrid[i][j] = 0;
				}
			}
			else
			{
				if (j == n-1)
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j]+grid[i][j+1]+grid[i+1][j+1];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
			}
		}
		else
		{
			if (i == n-1)
			{
				if (j == 0)
				{
					sumNeighbors = grid[i][j+1]+grid[i-1][j+1]+grid[i-1][j];
					printf("%d\n",sumNeighbors);
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j]+grid[i][j+1]+grid[i-1][j+1];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
			else
			{
				if (j == 0)
				{
					sumNeighbors = grid[i-1][j]+grid[i-1][j+1]+grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i-1][j]+grid[i-1][j-1]+grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i-1][j-1]+grid[i-1][j]+grid[i-1][j+1]+
										grid[i][j-1]+grid[i][j+1]+grid[i+1][j-1]+
										grid[i+1][j]+grid[i+1][j+1];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
		}
	}
	else
	{
		if (i == 0)
		{
			if (j == 0)
			{
				sumNeighbors = grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
				if(survive[sumNeighbors] == 1)
				{
					copyGrid[i][j] = 1;
				}
				else
				{
					copyGrid[i][j] = 0;
				}
			}
			else
			{
				if (j == n-1)
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j]+grid[i][j+1]+grid[i+1][j+1];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
			}
		}
		else
		{
			if (i == n-1)
			{
				if (j == 0)
				{
					sumNeighbors = grid[i][j+1]+grid[i-1][j+1]+grid[i-1][j];
					if(birth[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j]+grid[i][j+1]+grid[i-1][j+1];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
			else
			{
				if (j == 0)
				{
					sumNeighbors = grid[i-1][j]+grid[i-1][j+1]+grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
					if(birth[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i-1][j]+grid[i-1][j-1]+grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i-1][j-1]+grid[i-1][j]+grid[i-1][j+1]+
										grid[i][j-1]+grid[i][j+1]+grid[i+1][j-1]+
										grid[i+1][j]+grid[i+1][j+1];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
		}
	}
}

void newGrid(int n, int** grid, int** copyGrid)
{
	int i,j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			newCell(n,i,j,grid,copyGrid);
		}
	}
}

void freeGrid(int n, int** grid)
{
	int i;

	for (i=0; i<n; i++)
	{
		free(grid[i]);
	}

	free(grid);
}

int main()
{	
	int n = 10;
	int i,j;

	int** grid = mallocGrid(n);

	int** copyGrid = mallocGrid(n);

	initGrid(n,grid);
	grid[4][4] = 1;
	grid[4][5] = 1;
	grid[4][6] = 1;

	printGrid(n,grid);
	
	newGrid(n,grid,copyGrid);
	
	printf("\n \n");

	printGrid(n,copyGrid);

	freeGrid(n,grid);
	freeGrid(n,copyGrid);

	return 0;
}
