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
using namespace std;

//#define SPOS           16
#define BUFFER_SIZE    256
#define LESS_LENGTH    0


int SPOS = 16;

vector<string> myvector;// addr vector
vector<pair<string,int> > myvector2;//addr1 chu xian zai ji ge shu zu li mian
map<string,int > mymap2;//group key=add1 value=count(addr1)

//map<string,vector<int> > mymap3;//addr1,vector<gid>
//map<int,list<unsigned long> > mymap4;//g[] shu zu
//map<string,int> mymap5;//addr2  gid

map<string, vector<string> > mymap;//group key=addr2 value = addr1
map<string, vector<string> > mymap3;//addr1,addr2
map<string,list<unsigned> > mymap4;//addr2,g[]


char* b;//split1
char* c;//split2
char* d;//split3

const double collision = 0.001;
	
unsigned int pow(unsigned int i,unsigned int j);
unsigned int mypow(unsigned int i,unsigned int j);
	
unsigned int length = 0;
unsigned int* key_key1 = 0; 


void myinsert(char* addr2,char* addr1);

void vec_uniq();//vector qu chong
void tongjikey();//tongji key1

char* mysplit(char* a, int spos);//addr2
char* mysplit2(string a, int spos);//addr1
char* mysplit3(char* a, int spos);//addr1

//¹¹½¨mymap4
void myprint();
void myprint2();

int cmp(const pair<string,int> &x,const pair<string,int>&y);
void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec);
list<unsigned int> operator*(list<unsigned int> aa, list<unsigned int> bb);
void findMkey();
void make_map3();
unsigned int test_g(string addr1);

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
void make_primes_pool(unsigned int min,unsigned int max);
//void myprint1();

map <string, HashGroup> hash_map;
vector<unsigned int> primes_array;

int main(int argc,char* argv[])
{
	
	FILE* file;	
	file = fopen("rrc14_201209010000_v4.txt","r");
//	file = fopen("data_test","r");
	char* buffer; 
	char buffer2[BUFFER_SIZE];
	char* addr2;
	char* addr1;
	
	if(argc == 2)
		SPOS = atoi(argv[1]);
	
	 length = pow((unsigned int)2,(unsigned int)SPOS);
	key_key1 = new unsigned int[length]; 
	
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
	vec_uniq();
	tongjikey();
	myprint2();
	myprint();
       make_map3();
	findMkey();
	
	cout << "mul_hashtable_insert()" << endl;
	mul_hashtable_insert();
	cout << "count()" << endl;
	count_primes();

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
	return x.second > y.second;//descending order
}

void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec)
{
	for(map<string,int>::iterator iter = t_map.begin(); iter != t_map.end(); iter++)
	{
		t_vec.push_back(make_pair(iter->first,iter->second));
	}

	sort(t_vec.begin(),t_vec.end(),cmp);
}

unsigned int addr1_to_integer(string addr1)
{
	unsigned int addr1_i = 0;
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


void make_primes_pool(unsigned int min,unsigned int max)
{
	
	for(unsigned int i = min; i <= max; i++)
	{
		if(mul_is_prime(i))
		{
			primes_array.push_back(i);
		}
	}
	
	
}

void mul_hashtable_insert()
{
	make_primes_pool(1,4*length);
	for(map<string, vector<string> >::iterator iter = mymap.begin(); iter != mymap.end(); ++iter)
	{	
		HashGroup* hg = new HashGroup();
		hg->nBlocks = 2;
		hg->primes = new unsigned int[2]();
		hg->used = new unsigned int[2]();
		hg->Block = new unsigned int* [2]();
		
		vector<string> addr1_v = iter->second;
		unsigned int min = addr1_v.size() / hg->nBlocks;
		
		unsigned int prime_1 = 0, prime_2 = 0;
		
		
		for(vector<unsigned>::iterator its = primes_array.begin(); its != primes_array.end(); ++its)
		{
			unsigned int collision_num = 0;
			if(*its >= min)
			{
				prime_1 = *its;
				prime_2 = *its;
				
				hg->Block[0] = new unsigned int[prime_1]();
				hg->primes[0] = prime_1;
				hg->primes[1] = prime_2;

				//list<unsigned int> processing_list;
				list<unsigned int> pending_list;

				for(vector<string>::iterator it = addr1_v.begin(); it != addr1_v.end(); ++it)
				{
					unsigned int g = addr1_to_integer(*it);
					unsigned int hash_num = key_key1[g];
			
					unsigned int loc = hash_num % prime_1;
			
					if(hg->Block[0][loc] == 0)
					{
						hg->Block[0][loc] = 2;
						++hg->used[0];
					}
					else
					{
						pending_list.push_back(hash_num);	
							//cout << "haha" << endl;
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
						}
						else
						{
							++collision_num;
						}
				
					}
				}
				else
					hg->primes[1] = 0;
				
				if(((double)collision_num/addr1_v.size() <= collision))
				{
					break;
				}
				else if (prime_1 != primes_array.back())
				{
					delete [] hg->Block[0];
					delete [] hg->Block[1];
					hg->used[0] = 0;
					hg->used[1] = 0;
				}
				else
				{
					cout << "chongtu lv guo xiao" << endl;
				}
			}
				
		}
		hash_map.insert(make_pair(iter->first,*hg));
		delete hg;
		hg = NULL;
	}
}

void count_primes()
{
	char filename[100];
	sprintf(filename, "remap_array_use%d.txt", SPOS);

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

void make_map3()
{
	map<string,vector<string> >::iterator it = mymap.begin();
	while(it != mymap.end())
	{
		vector<string> addr1_v = mymap[it->first];
		vector<string>::iterator it2 = addr1_v.begin();
		while(it2 != addr1_v.end())
		{
			vector<string> a;
			a.push_back(it->first);
			pair<map<string, vector<string> >::iterator, bool>  ret = mymap3.insert(make_pair(*it2,a));

			if(!ret.second)
			{
				(ret.first->second).push_back(it->first);
				
			}
			
			
			it2++;
		}
		it++;
	}
}

void findMkey()
{

	
	for(int i = 0; i != myvector2.size();i++)
	{
		string addr1 = myvector2[i].first;
		unsigned int g,addr1_a = 0;
		
		for(int k = addr1.size()-1,j =0 ; k >= 0; k--,j++)
		{
			if(addr1[k] == '1')
			{
				addr1_a = addr1_a + pow((unsigned)2,(unsigned)j);
				
			}
		}
		
		g = test_g(addr1);
		key_key1[addr1_a] = g;
		

	}
	

}

unsigned int test_g(string addr1)
{
	unsigned int g;
	vector<string> gid = mymap3[addr1];
	unsigned int h,k;
	
	list<unsigned int> g_array1 = mymap4[gid[0]];

	for(int i = 1; i < gid.size(); i++)
	{
		
		g_array1 = g_array1 * mymap4[gid[i]];
		
		if(g_array1.empty())
		{
			break;
		}
	}

	if(g_array1.empty())
	{
		unsigned int m,n = 0;
		
		for(int i = 0; i < gid.size(); i++)
		{
			list<unsigned int> g_array3 = mymap4[gid[i]];
			m = g_array3.back();
			if(m > n)
				n = m;		
		}
		for(int i = 0; i < gid.size(); i++)
		{
			list<unsigned int> g_array4 = mymap4[gid[i]];
			unsigned int p = g_array4.back();
			if(p == n)
			{
				mymap4[gid[i]].pop_back();
				mymap4[gid[i]].push_back(n+1);
				
			}
			else
			{
				for(int r = p+1; r < n; r++)
				{
					mymap4[gid[i]].push_back(r);
				}
				mymap4[gid[i]].push_back(n+1);
			}
			
		}
		return n;
	}
	else
	{
		unsigned int j = g_array1.front();
		for(int i = 0; i < gid.size(); i++)
		{
			list<unsigned  int> g_array2 = mymap4[gid[i]];
			unsigned int l = g_array2.back();
			if(l == j)
			{
				mymap4[gid[i]].pop_back();
				mymap4[gid[i]].push_back(l+1);
				
			}
			else{
				mymap4[gid[i]].remove(j);
			}
		}
		return j;
	}
}

unsigned  int pow(unsigned int i,unsigned int j)
{
     if (j == 0)
         return 1;
     else 
         return i * pow(i,j-1);  
} 


list<unsigned int> operator*(list<unsigned int> aa, list<unsigned int> bb)
{
    list<unsigned int> dd;
 
    for(list<unsigned int>::iterator it = bb.begin(); it != bb.end(); it++)
    {
         if(find(aa.begin(),aa.end(),*it) != aa.end())
               dd.push_back(*it);
    }
    return dd;
}

void myprint()
{
	map<string, vector<string> >::iterator it = mymap.begin();
	while (it != mymap.end())
	{
		int j = 0;
		list<unsigned int> a;
		a.push_back(0);

		mymap4.insert(make_pair(it->first,a));
		
		++it;
	}

}

void myprint2()
{
	vector<pair<string,int> > v_result2;
	sortMapbyValue(mymap2,v_result2);
	
	myvector2 = v_result2;

}


