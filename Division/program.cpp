#include <cstdio>

int N;
int currentNumber[5];
int current;

bool isPair(int number)
{
	if(number <10000) return false;
	bool used[10];
	for(int i=0; i<10; i++) used[i] = false;
	int currentDigit;

	for(int i=0;i<5;i++) used[currentNumber[i]] = true;

	while(number != 0)
	{
		currentDigit = number%10;
		number/=10;

		if(used[currentDigit])
			return false;

		used[currentDigit] = true;
	}

	return true;
}

void setFirstNumber()
{
	currentNumber[0] = 1;
	currentNumber[1] = 0;
	currentNumber[2] = 2;
	currentNumber[3] = 3;
	currentNumber[4] = 4;

	current = 10234;
}

bool validateCurrent()
{
	bool used[10];
	for(int i=0; i<10; i++) used[i] = false;
	int index = 4;

	if(current < 10000)
	{
		used[0] = true;
		currentNumber[0] = 0;
	}
	int number = current;
	int currentDigit;
	while(number != 0)
	{
		currentDigit = number%10;
		number/=10;

		if(used[currentDigit])
			return false;

		used[currentDigit] = true;
		currentNumber[index--] = currentDigit;
	}

	return true;
}

void moveToNextNumber()
{
	do
	{
		current++;
	}while(!validateCurrent());
}

bool processOne()
{
	scanf("%d", &N);
	if(N==0) return false;

	setFirstNumber();

	while(current < 98765)
	{
		int posiblePair = current * N;

		if(posiblePair > 98765)
			break;
		
		if(isPair(posiblePair))
		{
			printf("%d / %05d = %d\n", posiblePair, current, N);
		}

		moveToNextNumber();
	}

	return true;
}

int main()
{
	while(processOne());

	return 0;
}