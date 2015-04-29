#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <string.h>
#include <fstream>
#include <math.h>
#include <list>
#include <cmath>
using namespace std;

#define SPOS         5 
#define BUFFER_SIZE    256
#define LESS_LENGTH    0

map<string, vector<string> > mymap;//group key=addr2 value = addr1

vector<string> myvector;// addr vector

map<string,int > mymap2;//group key=add1 value=count(addr1)

vector<pair<string,int> > myvector2;//addr1 chu xian zai duo shao ge ji he shu zu li mian

map <string, HashGroup> hash_map;

char* b;//split1 addr2
char* c;//split2 addr1
char* d;//split3 addr1

unsigned int mypow(unsigned int i,unsigned int j);

unsigned int length = mypow((unsigned int)2,(unsigned int)SPOS);

unsigned int* key_key1 = new unsigned int[length];
unsigned int* key_key2 = new unsigned int[length];


void myinsert(char* addr2, char* buffer);

void vec_uniq();//vector qu chong
void tongjikey();//tongji key1

char* mysplit(char* a, int spos);//addr2
char* mysplit2(string a, int spos);//addr1
char* mysplit3(char* a, int spos);//addr1



int cmp(const pair<string,int> &x,const pair<string,int>&y);
void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec);

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
	
	memset(key_key2,0,length*sizeof(unsigned int));
	FILE* file;	
	file = fopen("data_test","r");
//	file = fopen("data_test","r");
	char* buffer; 
	char buffer2[BUFFER_SIZE];
	char* addr2;
	char* addr1;
	
	while(fgets(buffer2,BUFFER_SIZE,file))
//	while(fscanf(file,"%s",buffer2) != -1)
	{

		if(buffer2[strlen(buffer2)-1] == '\n')
			buffer2[strlen(buffer2)-1] = 0;

		buffer = strtok(buffer2," ");
	
		myvector.push_back(buffer);

		addr2 = mysplit(buffer,SPOS);

		if(addr2)
		{
			addr1 = mysplit3(buffer,SPOS);
			myinsert(addr2,addr1);
			delete[] d;
		}
		delete[] b;
	
	}
	
/*	
	vec_uniq();
	tongjikey();

*/
	fclose(file);
	return 0;
}

//qu chong
void vec_uniq()
{
	sort(myvector.begin(),myvector.end());
	myvector.erase(unique(myvector.begin(),myvector.end()),myvector.end());
	
}

//gen ju chai fen wei zhi tong ji addr1 de ge shu
void tongjikey()
{
	char* buff;
	for(vector<string>::iterator iter = myvector.begin();iter != myvector.end(); iter++)
	{
		buff = mysplit2(*iter,SPOS);
		if(buff)
		{
			pair<map<string, int>::iterator, bool > ret = mymap2.insert(make_pair(buff,1));
			if(!ret.second)
				++ret.first->second;
		delete[] c;
		}
	}
}


char* mysplit(char* a, int spos)
{
	int len = strlen(a);
	b = new char[50];
	memset(b,0,50);

	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = SPOS,j = 0; i < len; i++,j++)
	{
		b[j] = a[i];
	
	}

	return b;

}
char* mysplit2(string a, int spos)
{
	c = new char[50];
	memset(c,0,50);
	if(a.size() <= SPOS)
		return LESS_LENGTH;
	for(int i=0; i < SPOS; i++)
	{
		c[i] =  a[i];
	}
	return c;
}

char* mysplit3(char* a, int spos)
{
	int len = strlen(a);
	d = new char[50];
	memset(d,0,50);

	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = 0; i < SPOS; i++)
	{
		d[i] = a[i];

	}

	return d;

}

void myinsert(char* addr2,char* addr1)
{
	vector<string> a;
	a.push_back(addr1);
	
	pair<map<string, vector<string> >::iterator, bool>  ret = mymap.insert(make_pair(addr2,a));
	
	if(!ret.second)
	{
		(ret.first->second).push_back(addr1);
		sort(ret.first->second.begin(),ret.first->second.end());
		ret.first->second.erase(unique(ret.first->second.begin(),ret.first->second.end()),ret.first->second.end());
	}

}

int cmp(const pair<string,int> &x,const pair<string,int>&y)
{
	return x.second > y.second;
}

void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec)
{
	for(map<string,int>::iterator iter = t_map.begin(); iter != t_map.end(); iter++)
	{
		t_vec.push_back(make_pair(iter->first,iter->second));
	}

	sort(t_vec.begin(),t_vec.end(),cmp);
}

int addr1_to_integer(string addr1)
{
	int addr1_i = 0;
	for(int k = addr1.size()-1,j=0; k >= 0; k--,j++)
	{
		if(addr1[k] == '1')
		{
				addr1_i = addr1_i + mypow((unsigned int)2,(unsigned int)j);
		
		}
	}
	return addr1_i;
}

unsigned int mypow(unsigned int i,unsigned int j)
{
     if (j == 0)
         return 1;
     else 
         return i * mypow(i,j-1);  
} 




void mul_hashtable_create();
void prepare_hash_group(HashGroup& hg, int g);
int mul_is_prime(int num);
int find_prime_number(int g);

map <string, HashGroup> hash_map;

void prepare_hash_group(HashGroup* hg, int g)
{
	hg->primes = new int[hg.nBlocks];
	hg->used = new int[hg.nBlocks];
	hg->Block = new int*[hg.nBlocks];

	for(int i=0; i < hg->nBlocks; i++)
	{
		hg->primes[i] = find_prime_number(g);
	}
	for(int i=0; i < hg->nBlocks; i++)
	{
		hg->Block[i] = new int[hg->primes[i]];
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
void mul_hashtable_create()
{

	for(map<string, vector<string> >::iterator iter = mymap.begin(); iter != mymap.end(); iter++)
	{	
		HashGroup* hg = new HashGroup();
		hg->nBlocks = 2;
		prepare_hash_group(hg,iter->second.size());
		hash_map.insert(iter->first,*hg);
		delete hg;
	}
	
}

void mul_hashtable_insert()
{
	
}








