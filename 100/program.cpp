#include <cstdio>
#define MAXCACHED 1000001

int cycleLenghts[MAXCACHED];

int cycleLenght(int x)
{
	if(x < MAXCACHED && cycleLenghts[x] != 0)
	{
		return cycleLenghts[x];
	}

	int total;
	if(x%2 == 0)
	{
		total = 1 + cycleLenght(x/2);
	}
	else
	{
		total = 2 + cycleLenght((3*x + 1)/2);
	}

	if(x < MAXCACHED)
		cycleLenghts[x] = total;

	return total;
}

int processInput(int a, int b)
{
	int max = 0;
	int current;

	if(b<a)
	{
		int aux = a;
		a = b;
		b = aux;
	}

	for(int i=a; i<=b; i++)
	{
		current = cycleLenght(i);
		if(current > max)
			max = current;
	}

	return max;
}

int main()
{
	cycleLenghts[1] = 1;

	char line[3000];
	int a,b;
	int first = 1;
	while(gets(line))
	{
		

		sscanf(line,"%d %d",&a,&b);
		printf("%d %d %d\n",a ,b, processInput(a, b));
	}

	return 0;
}
