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

#define SPOS           16
#define BUFFER_SIZE    256
#define LESS_LENGTH    0




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

unsigned int pow(unsigned int i,unsigned int j);

unsigned length = pow((unsigned int)2,(unsigned int)SPOS);
unsigned int* key_key1 = new unsigned int[length]; 


void myinsert(char* addr2,char* addr1);

void vec_uniq();//vector qu chong
void tongjikey();//tongji key1

//¹¹½¨mymap4
void myprint();
void myprint2();
void myprint7();

char* mysplit(char* a, int spos);//addr2
char* mysplit2(string a, int spos);//addr1
char* mysplit3(char* a, int spos);//addr1



int cmp(const pair<string,int> &x,const pair<string,int>&y);
void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec);
list<unsigned int> operator*(list<unsigned int> aa, list<unsigned int> bb);
void findMkey();
void make_map3();
unsigned int test_g(string addr1);


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
		
		delete[] b;
	}
	
	vec_uniq();
	tongjikey();


	myprint2();
	myprint();
	

       make_map3();
	findMkey();

	//myprint2();
       // testprint();
	myprint7();
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

	ofstream outf2("result3.txt",ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());
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
		
		
		cout<< "key_key1[" << addr1  << "]    " << "value=" << g << endl;

		

	}
	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);

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
	//map<string,int> m_result;
	//vector<pair<string,int> > v_result;

	map<string, vector<string> >::iterator it = mymap.begin();
	//cout<<"groupid"<<"          "<<"addr2"<<"          "<<"count"<<endl;
	//int i = 0;
	//string bb = "0";
	//string cc = "0";
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
void myprint7()
{
	char filename[100];
	sprintf(filename, "%d_2result4.txt", SPOS);

	ofstream outf2(filename,ios::app);
	streambuf *default_buff2 = cout.rdbuf();
	cout.rdbuf(outf2.rdbuf());
	unsigned long long int sum = 0;

	for(map<string,list<unsigned> >::iterator iter = mymap4.begin(); iter != mymap4.end(); iter++)
	{
		sum += (unsigned long long)(iter->second.back());
		//printf("haha\n");
	}

	cout << "sum=" << sum << endl;

	outf2.flush();
	outf2.close();
	cout.rdbuf(default_buff2);
}

