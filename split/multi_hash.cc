#include <iostream>
#include <string>
using namespace std;

struct HashGroup
{
	int nBlocks;
	int* primes;
	int* used;
	int** Block;
};
typedef struct HashGroup HashGroup;

typedef struct Node
{
	string addr1;
	string next_hop;
}Node;

void multi_hash_insert();
void prepare_hash_group(HashGroup& hg, int g);
int mul_is_prime(int num);
int find_prime_number(int g);


int main()
{
	multi_hash_insert();	
	cout << "hello world!" << endl;
	return 0;
}

void prepare_hash_group(HashGroup& hg, int g)
{
	hg.primes = new int[hg.nBlocks];
	hg.used = new int[hg.nBlocks];
	hg.Block = new int*[hg.nBlocks];

	for(int i=0; i < hg.nBlocks; i++)
	{
		hg.primes[i] = find_prime_number(g);
	}
	for(int i=0; i < hg.nBlocks; i++)
	{
		hg.Block[i] = new int[hg.primes[i]];
	}
}

int find_prime_number(int g)
{
	int prime = 1;

	for(g = g - 1; g > 0; g--)
	{
		if(mul_is_prime(g))
		{
			prime = g;
			break;
		}
	}
	return prime;
}

int mul_is_prime(int num)
{
	int i;
	int prime = 1;

	for(i = num/2; i > 1; i--)
	{
		if(num % i == 0)
		{
			prime = 0;
			break;
		}
	}
	return prime;
}
void multi_hash_insert()
{
	HashGroup hg;
	hg.nBlocks = 2;
	prepare_hash_group(hg,10);
	cout << "hg.prime[0]=" << hg.primes[0] << endl; 
}








