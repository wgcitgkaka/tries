#include <iostream>

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


int main()
{
	
	cout << "hello world!" << endl;
	return 0;
}

void prepare_hash_group(HashGroup& hg)
{
	hg.primes = new int[hg.nBlocks];
	hg.used = new int[hg.nBlocks];
	hg.Block = new int*[hg.nBlocks];

	for(int i=0; i < hg.nBlocks; i++)
	{
		hg.Block[i] = new int[hg.primes[i]]
	}
}

void make_Hash_table(Node node1)
{
	
}

void find_prime_number()
{

}










