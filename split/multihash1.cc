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

#define SPOS         16 
#define BUFFER_SIZE    256
#define LESS_LENGTH    0

map<string, vector<string> > mymap;//group key=addr2 value = addr1

vector<string> myvector;// addr vector

map<string,int > mymap2;//group key=add1 value=count(addr1)

vector<pair<string,int> > myvector2;//addr1 chu xian zai duo shao ge ji he shu zu li mian

char* b;//split1 addr2
char* c;//split2 addr1
char* d;//split3 addr1

unsigned int mypow(unsigned int i,unsigned int j);

unsigned int length = mypow((unsigned int)2,(unsigned int)SPOS);

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
	unsigned int nBlocks;
	unsigned int* primes;
	unsigned int* used;
	unsigned int** Block;
};
typedef struct HashGroup HashGroup;

typedef struct Node
{
	string addr1;
	string next_hop;
}Node;


void count_primes();
void mul_hashtable_insert();
unsigned int mul_is_prime(unsigned int num);
vector<unsigned int> find_prime_vector(unsigned int min,unsigned int max);
//void myprint1();

map <string, HashGroup> hash_map;


int main()
{
	
	FILE* file;	
	file = fopen("rrc14_201209010000_v4.txt","r");
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
	//cout << "create()" << endl;
	//mul_hashtable_create();
	cout << "mul_hashtable_insert()" << endl;
	mul_hashtable_insert();
	cout << "count()" << endl;
	count_primes();
//	myprint1();
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
	//string s = addr1;
	
	pair<map<string, vector<string> >::iterator, bool>  ret = mymap.insert(make_pair(addr2,a));
	
	if(!ret.second)
	{
		if(find(ret.first->second.begin(),ret.first->second.end(),addr1) == ret.first->second.end())
               			(ret.first->second).push_back(addr1);

/*		(ret.first->second).push_back(addr1);
		sort(ret.first->second.begin(),ret.first->second.end());
		ret.first->second.erase(unique(ret.first->second.begin(),ret.first->second.end()),ret.first->second.end());
*/
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

/*
//g dai biao mei ge hash zu zhong addr1 de ge shu
void prepare_hash_group(HashGroup* hg, int g)
{
	hg->primes = new int[hg->nBlocks];
	hg->used = new int[hg->nBlocks];
	hg->Block = new int*[hg->nBlocks];
	
	for(int i = 0; i < hg->nBlocks; i++)
	{
		memset(hg->used,0,hg->nBlocks*sizeof(int));
	}
	for(int i=0; i < hg->nBlocks; i++)
	{
		hg->primes[i] = find_prime_number(g);
	}
	for(int i=0; i < hg->nBlocks; i++)
	{
		hg->Block[i] = new int[hg->primes[i]];
		memset(hg->Block[i],0,hg->primes[i]*sizeof(int));   //初始化二维数组
	}
}

int find_prime_number(int g)
{
	int prime = 1;
	int m = 1000;
	int n = 100;
	int num0 = 0;
	int num1 = 0;
	int distance0 = 0;
	int distance1 = 0;
	int distance = 0;
	int tmp = 0;

	vector<int> prime_array;

	for(int i = g; i <= g + m*n; i++)
	{
		if(mul_is_prime(i))
		{
			prime_array.push_back(i);
		}
	}
	for(vector<int>::iterator it = prime_array.begin(); it != prime_array.end(); it++)
	{
		for(int i = 0;;i++)
		{
			num0 = mypow(2,i);
			if(num0 > *it)
				break;
		}
		num1 = num0 / 2;
		distance0 = *it - num1;
		distance1 = num0 - *it;
		distance = (distance0 < distance1 ? distance0:distance1);
		
		if(distance > tmp)
		{
			tmp = distance;
			prime = *it;
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
		hash_map.insert(make_pair(iter->first,*hg));
		delete hg;
	}
	
}

void mul_hashtable_insert()
{
	for(map<string, vector<string> >::iterator iter = mymap.begin(); iter != mymap.end(); iter++)
	{	
		vector<string> addr1_v = iter->second;
		HashGroup hg = hash_map[iter->first];
		for(vector<string>::iterator it = addr1_v.begin(); it != addr1_v.end(); it++)
		{
			unsigned int hash_num = addr1_to_integer(*it);
			for(int i = 0; i < hg.nBlocks-1; i ++)
			{
				unsigned int prime = hg.primes[i];
				unsigned int loc = hash_num % prime;
				
				if(hg.Block[i][loc] != 0 && hg.Block[i+1][loc] != 0)
				{
					cout << "chongtu" << endl;
					break;
				}

				if(hg.Block[i][loc] == 0 && hg.Block[i+1][loc] == 0)
				{
					if(hg.used[i] <= hg.used[i+1])
					{
						hg.Block[i][loc] = 2;
						hg.used[i]++;
					}
					else 
					{
						hg.Block[i+1][loc] = 2;
						hg.used[i+1]++;
					}
				}
				else if(hg.Block[i][loc] == 0)
				{
					hg.Block[i][loc] = 2;
					hg.used[i]++;
				}
				else
				{
					hg.Block[i+1][loc] = 2;
					hg.used[i+1]++;
				}
					
			}
			
		}
	}
}
*/

unsigned int mul_is_prime(unsigned int num)
{
	unsigned int i;
	unsigned int prime = 1;

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


vector<unsigned int> find_prime_vector(unsigned int min,unsigned int max)
{
	vector<unsigned int> prime_array;

	for(unsigned int i = min; i <= max; i++)
	{
		if(mul_is_prime(i))
		{
			prime_array.push_back(i);
		}
	}
	
	return prime_array;
	
}
void mul_hashtable_insert()
{
	for(map<string, vector<string> >::iterator iter = mymap.begin(); iter != mymap.end(); iter++)
	{	
		vector<string> addr1_v = iter->second;
		HashGroup* hg = new HashGroup();

		hg->nBlocks = 2;
		hg->primes = new unsigned int[2]();
		hg->used = new unsigned int[2]();
		hg->Block = new unsigned int* [2]();

		unsigned int min=0, max = 0;
		min = addr1_v.size() / hg->nBlocks;
		max = 2 * addr1_v.size();

		unsigned int prime_1 = 0, prime_2 = 0;

		vector<unsigned int> primes = find_prime_vector(min+1,max);
		prime_1 = primes.back();
		prime_2 = primes.front();

		hg->Block[0] = new unsigned int[prime_1]();
		hg->primes[0] = prime_1;
		hg->primes[1] = prime_2;

		//list<unsigned int> processing_list;
		list<unsigned int> pending_list;

		for(vector<string>::iterator it = addr1_v.begin(); it != addr1_v.end(); ++it)
		{
			unsigned int hash_num = addr1_to_integer(*it);
						
			unsigned int loc = hash_num % prime_1;
			
			if(hg->Block[0][loc] == 0)
			{
				hg->Block[0][loc];
				++hg->used[0];
			}
			else
			{
				pending_list.push_back(hash_num);	
				cout << "haha" << endl;
			}
			
		}
		if(!pending_list.empty())
		{			
			hg->Block[1] = new unsigned int[prime_2]();
			for(list<unsigned int>::iterator it = pending_list.begin(); it != pending_list.end(); ++it)
			{
				unsigned int loc2 = *it % prime_2;
				if(hg->Block[1][loc2] == 0)
				{	
					hg->Block[1][loc2] = 2;
					++hg->used[1];
			//		cout << "haha" << endl;
				}
				else
				{
					cout << "chongtu" << endl;
				}
				
			}
		}
		else
			hg->primes[1] = 0;

		hash_map.insert(make_pair(iter->first,*hg));
		delete hg;
		hg = NULL;
	}
}

void count_primes()
{
	char filename[100];
	sprintf(filename, "mul_array_use%d.txt", SPOS);

	unsigned long long int count = 0;
	double use = 0.0;
	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());
	for(map<string, vector<string> >::iterator iter = mymap.begin(); iter != mymap.end(); iter++)
	{	
		HashGroup hg = hash_map[iter->first];
		for(int i = 0; i < hg.nBlocks; i++)
		{
			count = count + (unsigned long long int)(hg.primes[i]);
			if(hg.primes[i] != 0)
			{			
				use = (double)(hg.used[i])/(double)(hg.primes[i]);
				cout << use << endl;
			}
		}
		
	}
	
	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);
	cout << "count= " << count << endl;
	
}

/*void myprint1()
{
	int i = 0;
	for(map<string, vector<string> >::iterator iter = mymap.begin(); iter != mymap.end(); iter++)
	{
		i += iter->second.size();	
	}
	cout << "total:" << i << endl;
	cout << "size:" << mymap.size() << endl;
}
*/




