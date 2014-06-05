#include <iostream>
#include <vector>
#include <cmath>

#define MAX_RING 207;
using namespace std;

vector<int> primes;
vector<int> possiblePrimes;
int combinations[12];
int combinationsCache[40][40];
int primesProduct = 1;

bool isDivisible(int number, int divisor)
{
	int x = number/divisor;
	return divisor*x == number;
}

bool isPrime(int possiblePrime)
{
	int sqr = sqrt(possiblePrime);
	int size = primes.size();
	for(int i=0; i<size && primes[i] <= sqr;i++)
	{
		if(isDivisible(possiblePrime, primes[i]))
			return false;
	}
	
	return true;
}

bool isCoprime(int possiblePrime, int largestIndex)
{
	for(int i=0; i<largestIndex;i++)
	{
		if(isDivisible(possiblePrime, primes[i]))
			return false;
	}
	
	return true;
}

int lastJump = 2;

int getNextJump()
{
	if(lastJump == 2)
	{
		return lastJump = 4;
	}
	return lastJump = 2;
}


int calculatePrimesTo(int max)
{
	int total = 12;
	if(primes.size() == 0 || primes.back() < max)
	{
		
		if(primes.size() == 0)
		{
			primes.push_back(2);
			primes.push_back(3);
			primes.push_back(5);
			primes.push_back(7);
			primes.push_back(11);
			primes.push_back(13);
			primes.push_back(17);
			primes.push_back(19);
			primes.push_back(23);
			primes.push_back(29);
			primes.push_back(31);
			primes.push_back(37);
		}
			
		for(int possiblePrime = primes.back() + getNextJump(); possiblePrime < max; possiblePrime+=getNextJump())
		{
			if(isPrime(possiblePrime))
			{
				primes.push_back(possiblePrime);
				total++;
			}
		}
	}
	
	return total;
}

void calculatePossiblePrimesTo(int numberOfPrimesToMultiply)
{	
	for(int i=0; i<numberOfPrimesToMultiply;i++)
	{
		primesProduct *= primes[i];
	}
	
	lastJump=2;
	
	for(int i=1; i<primesProduct; i+=getNextJump())
	{
		if(isCoprime(i, numberOfPrimesToMultiply))
		{
			possiblePrimes.push_back(i);
		}
	}
}

bool containsInRange(vector<int> *array, int left, int right, int search, int* hint)
{
	if(left < 0) left =0;
	if(left >= array->size()) left = array->size() - 1;
	if(right < 0) right =0;
	if(right >= array->size()) right = array->size() - 1;
	
	while(left <= right)
	{
		*hint = (right + left)/2;
		if((*array)[*hint] == search)
		{
			return true;
		}
		
		if((*array)[*hint] < search)
		{
			left = *hint + 1;
		}
		else
		{
			right = *hint -1;
		}
	}
	
	*hint = right;
	return false;
}

bool contains(vector<int> *array, int search, int* hint)
{
	return containsInRange(array, 0, array -> size() - 1, search, hint);
}

void decompose(int number, int delta)
{
	if(number <= 1)
		return;
	
	int divisorIndex = 0;
	
	while(number != 1)
	{
		while(number % primes[divisorIndex] == 0)
		{
			number /= primes[divisorIndex];
			combinations[divisorIndex] += delta;
		}
		
		divisorIndex ++;
	}	
}

int calcCombinations(int n, int k)
{
	if(combinationsCache[n][k] != -1)
		return combinationsCache[n][k];
	
	int maxPrimeIndex = 12;
	for(int i=0; i< maxPrimeIndex; i++)
		combinations[i] = 0;
		
	int biggerDenominator = n-k;
	int smallerDenominator = k;
	
	if(biggerDenominator < smallerDenominator)
	{
			smallerDenominator = n-k;
			biggerDenominator = k;
	}
	
		
	for(int i=biggerDenominator + 1; i<=n; i++)
		decompose(i, 1);
	
	for(int i=2; i<=smallerDenominator; i++)
		decompose(i, -1);
		
	int result = 1;
	
	for(int i=0;i<maxPrimeIndex; i++)
	{
		for(int j=0;j<combinations[i]; j++)
			result*=primes[i];
	}
	
	return combinationsCache[n][n-k] = combinationsCache[n][k] = result;
}

int firstOffsetIndexAfter(int x, int hint, bool* inNextRing)
{
	if(hint<0) hint = 0;
	*inNextRing = false;
	for(int i=hint; i<possiblePrimes.size();i++)
	{
		if(possiblePrimes[i]>=x)
			return i;
	}
	
	*inNextRing = true;
	return 0;
}

int numberInRing(int ring, int offsetIndex)
{
	return ring * primesProduct + possiblePrimes[offsetIndex];
}

void moveToNextIndex(int* ring, int* index)
{
	(*index)++;
	if((*index) >= possiblePrimes.size())
	{
		*index = 0;
		(*ring)++;
	}
}

int calculate(int intervalMin, int intervalMax, int length, int distance)
{
	int total = 0;
	if(intervalMax - intervalMin < distance)
		return total;
	
	int lowerBound = intervalMin;
	if (intervalMin < primes.back())
	{
		int indexOfFirstPrime;
		contains(&primes, intervalMin, &indexOfFirstPrime);
		if(indexOfFirstPrime < 0) indexOfFirstPrime = 0;
		
		for(;indexOfFirstPrime<primes.size();indexOfFirstPrime++)
		{
			if(primes[indexOfFirstPrime] > intervalMin)
				break;
		}
					
		for(int lowerIndex = indexOfFirstPrime; 
				lowerIndex < primes.size() &&
				intervalMax - (lowerBound = primes[lowerIndex]) >= distance &&
				primes.back() - primes[lowerIndex] >= distance; lowerIndex++)
		{			
			int inverse = distance + primes[lowerIndex];
			int indexOfInverse;
		
			if(!containsInRange(&primes, lowerIndex + 1, lowerIndex + 16, inverse, &indexOfInverse) || indexOfInverse - lowerIndex + 1 < length)
				continue;
				
			total += calcCombinations(indexOfInverse - lowerIndex -1, length - 2);	
		}
	}
	
	int ringIndex = lowerBound / primesProduct;
	
	int offsetOfFirstPossiblePrime = lowerBound % primesProduct;
	int indexOfFirstOffset;
	bool inNextRing;
	contains(&possiblePrimes, offsetOfFirstPossiblePrime, &indexOfFirstOffset);
	int lowerOffsetIndex = firstOffsetIndexAfter(offsetOfFirstPossiblePrime, indexOfFirstOffset, &inNextRing);
	
	if(inNextRing)
		ringIndex ++;
	
	for(; intervalMax - numberInRing(ringIndex, lowerOffsetIndex) >= distance; moveToNextIndex(&ringIndex, &lowerOffsetIndex))
	{
		int inverse = distance + possiblePrimes[lowerOffsetIndex];
		int indexOfInverseOffset;
		
		int leftPossibleIndex = lowerOffsetIndex + 1;
		int rightPossibleIndex = lowerOffsetIndex + 16;
		int inverseRingIndex = ringIndex;
		if(inverse >= primesProduct)
		{
			inverse -= primesProduct;
			leftPossibleIndex = 0;
			rightPossibleIndex = 15;
			inverseRingIndex = ringIndex + 1;
		}
			
		if(!containsInRange(&possiblePrimes, leftPossibleIndex, rightPossibleIndex, inverse, &indexOfInverseOffset))
			continue;
			
		int possiblePrimesInBetween;
		
		if(inverseRingIndex == ringIndex)
		{
			possiblePrimesInBetween = indexOfInverseOffset - lowerOffsetIndex + 1;
		}
		else
		{
			possiblePrimesInBetween = possiblePrimes.size() - lowerOffsetIndex + indexOfInverseOffset + 1;
		}
		
		if(possiblePrimesInBetween < length)
			continue;
			
		if(!isPrime(numberInRing(ringIndex, lowerOffsetIndex)) ||
			!isPrime(numberInRing(inverseRingIndex, indexOfInverseOffset)))
			continue;
			
		int totalPrimes = 2;		
		
		int ringStart = ringIndex * primesProduct;
		int currentPossibleIndex = lowerOffsetIndex;
		int currentPossibleRingIndex = ringIndex;
		for(moveToNextIndex(&currentPossibleRingIndex, &currentPossibleIndex);
			possiblePrimesInBetween >= length && (currentPossibleRingIndex != inverseRingIndex || currentPossibleIndex != indexOfInverseOffset);
			moveToNextIndex(&currentPossibleRingIndex, &currentPossibleIndex))
		{
			if(isPrime(numberInRing(currentPossibleRingIndex, currentPossibleIndex)))
				totalPrimes++;
			else
				possiblePrimesInBetween--;
		}
		
		if(totalPrimes >= length)
		{
			total += calcCombinations(totalPrimes - 2, length - 2);	
		}
	}
	
	return total;
}

int main()
{
	for(int i=0;i<40;i++)
		for(int j=0;j<40;j++)
			combinationsCache[i][j] = -1;
			
	calculatePrimesTo(44721);
	calculatePossiblePrimesTo(8);
	
	int totalTests = 0;
	int intervalMin, intervalMax, length, distance;
	
	cin>>totalTests;
	
	for(int i=0; i<totalTests; i++)
	{
		cin>>intervalMin>>intervalMax>>length>>distance;
		cout<<calculate(intervalMin, intervalMax, length, distance)<<endl;
		//cout<<calculate(57149120, 57149160, 3, 36);
		//cout<<calculate(57149124, 57149160, 3, 36);
		//if (i < totalTests - 1)
		//	cout << endl;
	}
	
	return 0;
}

