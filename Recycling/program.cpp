#include <cstdio>
#define TOTAL 100

int cities[100][5];
int deltas[100][101];
int totalCities;

int indexes[256];

void initIndexes()
{
	indexes['r']=0;
	indexes['o']=1;
	indexes['y']=2;
	indexes['g']=3;
	indexes['b']=4;
}

void parseCity(char* line, int* city)
{
	//          111111111
	//0123456789012345678
	//r/P,o/G,y/S,g/A,b/N
	city[indexes[line[0]]] = line[2];
	city[indexes[line[4]]] = line[6];
	city[indexes[line[8]]] = line[10];
	city[indexes[line[12]]] = line[14];
	city[indexes[line[16]]] = line[18];
}

int delta(int* city1, int* city2)
{
	int currentDelta = 0;
	for(int i=0;i<5;i++)
	{
		if(city1[i] != city2[i]) currentDelta++;
	}

	return currentDelta;
}

bool processOne()
{
	char currentLine[100];
	totalCities = 0;
	int currentCity = 0;
	int currentDelta;
	int indexMin;
	int minDelta;

	while(true)
	{
		gets(currentLine);
		if(currentLine[0] == '#')
		{
			return false;
		}
		else if(currentLine[0] == 'e')
		{
			break;
		}

		parseCity(currentLine, cities[totalCities++]);

		deltas[currentCity][TOTAL] = 0;

		minDelta = 1000;

		for(int i=0; i<totalCities; i++)
		{
			int currentDelta = delta(cities[currentCity], cities[i]);
			deltas[currentCity][i] = deltas[i][currentCity] = currentDelta;
			deltas[currentCity][TOTAL] += currentDelta;
			deltas[i][TOTAL] += currentDelta;

			if(deltas[i][TOTAL] < minDelta)
			{
				minDelta = deltas[i][TOTAL];
				indexMin = i+1;
			}
		}

		currentCity++;
	}

	printf("%d\n", indexMin);

	return true;
}

int main()
{
	initIndexes();

	while(processOne());

	return 0;
}


/*
r/P,o/G,y/S,g/A,b/N  0 2 4 3  9
r/G,o/P,y/S,g/A,b/N  2 0 5 4  11
r/P,y/S,o/G,g/N,b/A  4 5 0 3  12
r/P,o/S,y/A,g/G,b/N  3 4 3 0  10
e
r/G,o/P,y/S,g/A,b/N
r/P,y/S,o/G,g/N,b/A
r/P,o/S,y/A,g/G,b/N
r/P,o/G,y/S,g/A,b/N
ecclesiastical
#

1
4
*/