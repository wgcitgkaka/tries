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


#define BUFFER_SIZE    256
#define LESS_LENGTH    0

const double collision = 0.001;

map<string, vector<string> > mymap;//group key=addr2 value = addr1

vector<string> myvector;// addr vector

map<string,int > mymap2;//group key=add1 value=count(addr1)

map<string,vector<int> > mymap3;//addr1,vector<gid>
map<int,list<unsigned long> > mymap4;//g[] shu zu
map<string,int> mymap5;//addr2  gid
map<string, list<unsigned long> > mymap6;//g[] id is addr2
map<string, vector<string> > mymap1;//addr1 addr2

vector<pair<string,int> > myvector2;//addr1 chu xian zai ji he shu zu li mian

char* b;//split1
char* c;//split2
char* d;//split3

unsigned long int mypow(unsigned long int i,unsigned long int j);

unsigned long length = 0;

unsigned long int* key_key1 = 0; 
unsigned long int* key_key2 = 0;
int SPOS = 16;

void myinsert(char* addr2, char* buffer);

void vec_uniq();//vector qu chong
void tongjikey();//tongji key1

//构建map4 map5
void myprint();
//构建myvector2
void myprint2();
//输出静态g1数组
void myprint3();
//输出动态g2数组
void myprint4();
//输出map总条目数
void myprint5();
void myprint6();
void myprint7();


char* mysplit(char* a, int spos);//addr2
char* mysplit2(string a, int spos);//addr1
char* mysplit3(char* a, int spos);//addr1



int cmp(const pair<string,int> &x,const pair<string,int>&y);
void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec);
list<unsigned long int> operator*(list<unsigned long int> aa, list<unsigned long int> bb);

void findMkey();
void make_map3();
unsigned long int test_g(string addr1);
unsigned long int test_g2(string s,string s1,unsigned long int g);

void testprint();

struct HashGroup
{
	unsigned int nBlocks;
	unsigned long int* primes;
	unsigned long int* used;
	unsigned long int** Block;
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
vector<unsigned long int> primes_array;

int main(int argc, char* argv[])
{
	if(argc == 2)
		SPOS = atoi(argv[1]);
	length = mypow((unsigned long int)2,(unsigned long int)SPOS);
	key_key1 = new unsigned long int[length](); 
	key_key2 = new unsigned long int[length]();
	
	//memset(key_key2,0,length*sizeof(unsigned long int));
	FILE* file;	
	file = fopen("unique_ipv4.txt","r");
//	file = fopen("data_test","r");
	char* buffer; 
	char buffer2[BUFFER_SIZE];
	char* addr2;
	char* addr1;
	
	while(fgets(buffer2,BUFFER_SIZE,file))
//	while(fscanf(file,"%s",buffer2) != -1)
	{
		
		buffer = strtok(buffer2," ");
		if(buffer2[strlen(buffer2)-1] == '\n')
			buffer2[strlen(buffer2)-1] = 0;
//		printf("%s\n",buffer);
//		printf("%s\n",buffer2);
		
		myvector.push_back(buffer);

		addr2 = mysplit(buffer,SPOS);

		if(addr2)
		{
			addr1 = mysplit3(buffer,SPOS);
			myinsert(addr2,addr1);
		//	printf("%s\n",addr2);
			delete[] d;
		}
		//mapprint();
//		printf("-----\n");
		delete[] b;
	}
	
	vec_uniq();
	tongjikey();


	myprint2();
	myprint();


       make_map3();
	findMkey();

	//myprint3();
	//myprint4();
	//myprint5();
	myprint6();
	myprint7();

	cout << "mul_hashtable_insert()" << endl;
	mul_hashtable_insert();
	cout << "count()" << endl;
	count_primes();

	fclose(file);
	return 0;
}


void vec_uniq()
{
	sort(myvector.begin(),myvector.end());
	myvector.erase(unique(myvector.begin(),myvector.end()),myvector.end());
	
}

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
//	b=(char*)malloc(256);
	b = new char[50];
	memset(b,0,50);
//	printf("length=%d\n",len);
	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = SPOS,j = 0; i < len; i++,j++)
	{
		b[j] = a[i];
	//	printf("%c\n",a[i]);
		
		//printf("hehe\n");
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
//	b=(char*)malloc(256);
	d = new char[50];
	memset(d,0,50);
//	printf("length=%d\n",len);
	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = 0; i < SPOS; i++)
	{
		d[i] = a[i];
	//	printf("%c\n",a[i]);
		
		//printf("hehe\n");
	}

	return d;

}

void myinsert(char* addr2,char* addr1)
{
	vector<string> a;
	a.push_back(addr1);

	vector<string> aa;
	aa.push_back(addr2);

	list<unsigned long> gshuzu;
	gshuzu.push_back(0);
	
	string s = addr1;
	string s1 = addr2;
/*	for(vector<string>::iterator iter = a.begin(); iter != a.end(); ++iter)
	{
//		printf("iter%s\n", (char*) *iter);
		cout << *iter << endl;
		cout << "haha" << endl;
	}
	
*/

	unsigned long int g,addr1_a = 0;
		
	for(int k = s.size()-1,j = 0 ; k >= 0; k--,j++)
	{
		if(s[k] == '1')
		{
			addr1_a = addr1_a + mypow((unsigned long)2,(unsigned long)j);
				
		}
	}
		
	
	g = key_key2[addr1_a];
		

	pair<map<string, list<unsigned long> >::iterator, bool>  ret2 = mymap6.insert(make_pair(addr2,gshuzu));
	
	if(!ret2.second)
	{
		pair<map<string, vector<string> >::iterator, bool>  ret = mymap.insert(make_pair(addr2,a));
	
		if(!ret.second)
		{
				
		//(ret.first->second).push_back(buffer);

			if(find(ret.first->second.begin(),ret.first->second.end(),s) == ret.first->second.end())

               			(ret.first->second).push_back(addr1);

		//sort(ret.first->second.begin(),ret.first->second.end());
		//ret.first->second.erase(unique(ret.first->second.begin(),ret.first->second.end()),ret.first->second.end());
		}
	
	

		pair<map<string, vector<string> >::iterator, bool>  ret1 = mymap1.insert(make_pair(addr1,aa));
	
		if(!ret1.second)
		{
				

			if(find(ret1.first->second.begin(),ret1.first->second.end(),s1) == ret1.first->second.end())
			{
               			(ret1.first->second).push_back(addr2);
				key_key2[addr1_a] = test_g2(s,s1,g);
			}

		}
		else
		{
			key_key2[addr1_a] = test_g2(s,s1,g);
		}
		
	
	}
	else
	{	

		mymap.insert(make_pair(addr2,a));

		pair<map<string, vector<string> >::iterator, bool>  ret3 = mymap1.insert(make_pair(addr1,aa));
	
		if(!ret3.second)
		{
				
			if(find(ret3.first->second.begin(),ret3.first->second.end(),s1) == ret3.first->second.end())
			{
               			(ret3.first->second).push_back(addr2);
				key_key2[addr1_a] = test_g2(s,s1,g);
			}

		}
		else
		{
			key_key2[addr1_a] = test_g2(s,s1,g);
		}
		
		//test_g2();
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





void make_map3()
{
	map<string,vector<string> >::iterator it = mymap.begin();
	while(it != mymap.end())
	{
		vector<string> addr1_v = mymap[it->first];
		vector<string>::iterator it2 = addr1_v.begin();
		while(it2 != addr1_v.end())
		{
			vector<int> a;
			a.push_back(mymap5[it->first]);
			pair<map<string, vector<int> >::iterator, bool>  ret = mymap3.insert(make_pair(*it2,a));

			if(!ret.second)
			{
				(ret.first->second).push_back(mymap5[it->first]);
				
			}
			
			
			it2++;
		}
		it++;
	}
}

void findMkey()
{

	/*char filename[100];
	sprintf(filename, "./result/%d_result3.txt", SPOS);
	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());*/
	for(unsigned int i = 0; i != myvector2.size();i++)
	{
		string addr1 = myvector2[i].first;
		unsigned long int g,addr1_a = 0;
		
		for(int k = addr1.size()-1,j =0 ; k >= 0; k--,j++)
		{
			if(addr1[k] == '1')
			{
				addr1_a = addr1_a + mypow((unsigned long)2,(unsigned long)j);
				
			}
		}
		
		g = test_g(addr1);
		key_key1[addr1_a] = g;
		
		
		//cout<< "key_key1[" << addr1  << "]    " << "value=" << g << endl;

		

	}
	/*outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);*/

}

unsigned long int test_g(string addr1)
{
	unsigned long int g;
	vector<int> gid = mymap3[addr1];
	unsigned long int h,k;
	
	list<unsigned long int> g_array1 = mymap4[gid[0]];

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
		unsigned long int m,n = 0;
		
		for(int i = 0; i < gid.size(); i++)
		{
			list<unsigned long int> g_array3 = mymap4[gid[i]];
			m = g_array3.back();
			if(m > n)
				n =m;		
		}
		for(int i = 0; i < gid.size(); i++)
		{
			list<unsigned long int> g_array4 = mymap4[gid[i]];
			unsigned long int p = g_array4.back();
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
		unsigned long int j = g_array1.front();
		for(int i = 0; i < gid.size(); i++)
		{
			list<unsigned long int> g_array2 = mymap4[gid[i]];
			unsigned long int l = g_array2.back();
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

unsigned long int test_g2(string s,string s1,unsigned long int g)
{
	list<unsigned long> g_array = mymap6[s1];
	unsigned long int mm = g_array.back();
	vector<string> gid_addr2 = mymap1[s];

	if (g > mm)
	{
		for(int i=mm+1; i < g ; i++)
			mymap6[s1].push_back(i);

		mymap6[s1].push_back(g+1);
		return g;
	}
	else if (g == mm)
	{
		mymap6[s1].pop_back();
		mymap6[s1].push_back(g+1);
		return g;
	}
	else
	{
		if(find(g_array.begin(),g_array.end(),g) != g_array.end())
		{
			mymap6[s1].remove(g);
			return g;
		}
		else
		{
			for(int i = 0; i < gid_addr2.size()-1; i++)
			{
			
				g_array = g_array * mymap6[gid_addr2[i]];
			
				if(g_array.empty())
				{
					break;
				}
			}
	
			if(g_array.empty())
			{
				unsigned long int m,n = 0;
				
				for(int i = 0; i < gid_addr2.size(); i++)
				{
					list<unsigned long int> g_array3 = mymap6[gid_addr2[i]];
					m = g_array3.back();
					if(m > n)
					n = m;		
				}
				for(int i = 0; i < gid_addr2.size(); i++)
				{
					list<unsigned long int> g_array4 = mymap6[gid_addr2[i]];
					unsigned long int p = g_array4.back();
					if(p == n)
					{
						mymap6[gid_addr2[i]].pop_back();
						mymap6[gid_addr2[i]].push_back(n+1);
					
					}
					else
					{
						for(int r = p+1; r < n; r++)
						{
							mymap6[gid_addr2[i]].push_back(r);
						}
						mymap6[gid_addr2[i]].push_back(n+1);
					}
					if(gid_addr2[i] != s1)
					{
						mymap6[gid_addr2[i]].push_back(g);
						mymap6[gid_addr2[i]].sort();
					}
				
				}
				return n;
			}
			else
			{
				unsigned long int j = g_array.front();
				for(int i = 0; i < gid_addr2.size(); i++)
				{
					list<unsigned long int> g_array2 = mymap6[gid_addr2[i]];
					unsigned long int l = g_array2.back();
					if(l == j)
					{
						mymap6[gid_addr2[i]].pop_back();
						mymap6[gid_addr2[i]].push_back(l+1);
						
					}
					else{
						mymap6[gid_addr2[i]].remove(j);
					}

					if(gid_addr2[i] != s1)
					{
						mymap6[gid_addr2[i]].push_back(g);
						mymap6[gid_addr2[i]].sort();
					}
				}
				return j;
			}	
		}		
		
	}
}

unsigned long int mypow(unsigned long int i,unsigned long int j)
{
     if (j == 0)
         return 1;
     else 
         return i * mypow(i,j-1);  
} 


list<unsigned long int> operator*(list<unsigned long int> aa, list<unsigned long int> bb)
{
    list<unsigned long int> dd;
 
    for(list<unsigned long int>::iterator it = bb.begin(); it != bb.end(); it++)
    {
         if(find(aa.begin(),aa.end(),*it) != aa.end())
               dd.push_back(*it);
    }
    return dd;
}

void myprint()
{
	char filename[100];
	sprintf(filename, "./result/%d_result_group.txt", SPOS); 	
	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());
	
	map<string,int> m_result;
	vector<pair<string,int> > v_result;

	map<string, vector<string> >::iterator it = mymap.begin();
	//cout<<"groupid"<<"          "<<"addr2"<<"          "<<"count"<<endl;
	unsigned int i = 0;
	//string bb = "0";
	//string cc = "0";
	while (it != mymap.end())
	{
		unsigned int j = 0;
		list<unsigned long int> a;
		a.push_back(0);

		//cc = "0";
		for(vector<string>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter)
		{
			j++;
			/*bb = *iter;
			if(bb > cc)
				cc = bb;*/
		//	cout<< i <<"    " << it->first <<"    "<< *iter <<"    "<< j << endl;
		}
//			ofstream outf("./result/result1.txt",ios::app);
//			streambuf *default_buff = cout.rdbuf();
//
//			cout.rdbuf(outf.rdbuf());
//
//			cout<< i <<"    " << it->first <<"    "<<  j<<"    " << endl;
//
//			outf.flush();
//			outf.close();
//			cout.rdbuf(default_buff);
			
			m_result.insert(make_pair(it->first,j));
			
			mymap5.insert(make_pair(it->first,i));

			mymap4.insert(make_pair(i,a));

		i++;
		++it;
	}

	sortMapbyValue(m_result,v_result);
	
	for(unsigned int k = 0; k < v_result.size(); k++)
	{
		
		cout << v_result[k].second << endl;


	}
	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);
}

void myprint2()
{
	vector<pair<string,int> > v_result2;
	sortMapbyValue(mymap2,v_result2);
	
	myvector2 = v_result2;

/*	vector<pair<string,int> >::iterator it = v_result2.begin();
	while(it != v_result2.end())
	{
		
			ofstream outf("./result/result2.txt",ios::app);
			streambuf *default_buff = cout.rdbuf();

			cout.rdbuf(outf.rdbuf());

			cout<<"key="<<it->first<<"      "<<"count="<< it->second << endl;
			
			outf.flush();
			outf.close();
			cout.rdbuf(default_buff);
			it++;
	
	}
*/
}

void myprint3()
{
	char* filename;
	sprintf(filename, "%d_result1.txt", SPOS);

	map<string, int>::iterator it = mymap5.begin();

	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());
	while(it != mymap5.end())
	{
		cout << "gid=" << it->second << "        addr2=" << it->first << endl;

		vector<string> a = mymap[it->first];
		for(int i = 0; i < a.size(); i++)
		{
			cout<< "addr1=" << a[i] << endl;
		}		
		
		
		list<unsigned long> aa = mymap4[it->second];
		cout<< "g[]={";
		for(list<unsigned long int>::iterator iter = aa.begin(); iter != aa.end(); iter++)
		{
			cout << *iter << ",";
		}
		cout << "}"<< endl;
		it++;

	}
	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);

}

void myprint4()
{
	map<string, list<unsigned long int> >::iterator it = mymap6.begin();
	int j = 0;

	ofstream outf2("./result/2result1.txt",ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());

	while(it != mymap6.end())
	{
		cout << "gid=" << j << "        addr2=" << it->first << endl;

		vector<string> a = mymap[it->first];
		for(int i = 0; i < a.size(); i++)
		{
			cout<< "addr1=" << a[i] << endl;
		}		
		
		list<unsigned long> aa = mymap6[it->first];
		
		
		cout<< "g[]={";
		for(list<unsigned long int>::iterator iter = aa.begin(); iter != aa.end(); iter++)
		{
			cout << *iter << ",";
		}
		cout << "}"<< endl << endl;
		it++;
		j++;

	}
	for (int m = 0 ; m < length; m++)
	{
		cout << key_key2[m] << "   ";
	} 

	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);

}

void myprint5()
{
	char filename[100];
	sprintf(filename, "./result/%d_2result2.txt", SPOS);

	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());
	
	cout << mymap.size() << endl;
	cout << endl;
		

	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);
}

void myprint6()
{
	char filename[100];
	sprintf(filename, "./result/%d_result.txt", SPOS); 
	
	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());

	
	unsigned long sum1 = 0;
	long double sum = 0.0;
	long double sd = 0.0;
	vector<unsigned long> aaa;
	//printf("haha1\n");
	for(map<string, vector<string> >::iterator iter = mymap.begin(); iter != mymap.end(); iter++)
	{
		aaa.push_back((unsigned long)(iter->second.size()));
		sum1 += (unsigned long)(iter->second.size());
		//printf("haha\n");
	}
	long double avg = sum1/(long double)mymap.size();
	
	for(vector<unsigned long>::iterator it = aaa.begin(); it != aaa.end() ; it++)
	{
		long double tmp = (long double)(*it) - (long double)avg;
		sum += tmp * tmp;
		//printf("haha2\n");
	}
	
	
	sd = sqrt(sum / mymap.size() );
	
	cout << "sum total = " << myvector.size() << endl;
	cout << "group_num = " << mymap.size() << endl;
	cout << "avg = " << avg << endl;
	cout << "SD = " << sd << endl;
	
		

	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);

	//cout << myvector.size() << endl;
	//cout << mymap.size() << endl;
}

void myprint7()
{
	char filename[100];
	sprintf(filename, "./result/%d_result.txt", SPOS);

	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());
	unsigned long long int sum = 0;
	unsigned long long int sum1 = 0;

	for(map<int,list<unsigned long> >::iterator iter = mymap4.begin(); iter != mymap4.end(); iter++)
	{
		sum += (unsigned long long)(iter->second.back());
		//printf("haha\n");
	}

	cout << "static=" << sum << endl;

	for(map<string,list<unsigned long> >::iterator iter = mymap6.begin(); iter != mymap6.end(); iter++)
	{
		sum1 += (unsigned long long)(iter->second.back());
		//printf("haha\n");
	}

	cout << "dynamic=" << sum1 << endl ;

	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);
}

/*
int calg(list<int>& g_list, int& split_pos) {
  sort(g_list.begin(), g_list.end());//从小到大

  size_t num = g_list.size();
  size_t i, j = 0;
  int total_mem = 0, continues_cnt = 0;

  while ((i = j) < num) {
    total_mem += split_pos; // the size of bits for key'

    continues_cnt = 1;
    for (j = i + 1 ; g_list[j] == g_list[j - 1] + 1 && j < num ; j ++){
      continues_cnt ++;
    };

    if (continues_cnt > 1) {
      total_mem += split_pos;// the maximum size of the count is the same as key'
    }
  }

  return total_mem;
}
*/

unsigned long int addr1_to_integer(string addr1)
{
	unsigned long int addr1_i = 0;
	for(int k = addr1.size()-1,j=0; k >= 0; k--,j++)
	{
		if(addr1[k] == '1')
		{
				addr1_i = addr1_i + mypow((unsigned long int)2,(unsigned long int)j);
		
		}
	}
	return addr1_i;
}

unsigned long int mul_is_prime(unsigned long int num)
{
	unsigned long int i;
	unsigned long int prime = 1;

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


void make_primes_pool(unsigned long int min,unsigned long int max)
{
	
	for(unsigned long int i = min; i <= max; i++)
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
		hg->primes = new unsigned long int[2]();
		hg->used = new unsigned long int[2]();
		hg->Block = new unsigned long int* [2]();
		
		vector<string> addr1_v = iter->second;
		unsigned long int min = addr1_v.size() / hg->nBlocks;
		
		unsigned long int prime_1 = 0, prime_2 = 0;
		
		
		for(vector<unsigned long>::iterator its = primes_array.begin(); its != primes_array.end(); ++its)
		{
			unsigned int collision_num = 0;
			if(*its >= min)
			{
				prime_1 = *its;
				prime_2 = *its;
				
				hg->Block[0] = new unsigned long int[prime_1]();
				hg->primes[0] = prime_1;
				hg->primes[1] = prime_2;

				//list<unsigned int> processing_list;
				list<unsigned long int> pending_list;

				for(vector<string>::iterator it = addr1_v.begin(); it != addr1_v.end(); ++it)
				{
					unsigned long int g = addr1_to_integer(*it);
					unsigned long int hash_num = key_key2[g];
			
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
					hg->Block[1] = new unsigned long int[prime_2]();
					for(list<unsigned long int>::iterator it = pending_list.begin(); it != pending_list.end(); ++it)
					{
						unsigned long int loc2 = *it % prime_2;
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
	sprintf(filename, "d_remap_array_use%d.txt", SPOS);

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

