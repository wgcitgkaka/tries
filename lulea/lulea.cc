#include “lulea.h”


void Lulea::init_lulea(Lulea* &plnode1,int n)
{
	int i;

	plnode1 = new Lnode();
	plnode1->info = new int[n];
	plnode1->length = new int[n];
	plnode1->lulea_bits = new int[n];

	for(i=0; i < n; i++)
	{
		plnode1->info[i] = 0;
		plnode1->length[i] = 0;
		plnode1->lulea_bits = 0;
	}

}


int Lulea::pow(int n)
{
	if(n == 0)
	{
		return 1;
	}
	else
	{
		return 1<<n;
	}
}
